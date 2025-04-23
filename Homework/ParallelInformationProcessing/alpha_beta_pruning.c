#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_NUM_THREADS 4
#define DEFAULT_TREE_SIZE 16
#define MAX_THREADS 64
#define MAX_PARALLEL_DEPTH 3

typedef struct {
    int depth;
    int nodeIndex;
    int isMax;
    int* scores;
    int alpha;
    int beta;
    int h;
    int result;
    pthread_mutex_t result_mutex;
    pthread_cond_t result_cond;
    int result_ready;
} ThreadData;

typedef struct {
    ThreadData* tasks[MAX_THREADS];
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int shutdown;
    int active_threads;
} WorkQueue;

WorkQueue work_queue;
pthread_t threads[MAX_THREADS];

int alphaBeta(int depth, int nodeIndex, int isMax, int* scores, 
             int alpha, int beta, int h, int parallel_depth);

void generate_scores(int* scores, int size) {
    unsigned int seed = time(NULL) + getpid();
    srand(seed);
    for (int i = 0; i < size; i++) {
        scores[i] = rand() % 200 - 100;
    }
}

void work_queue_init() {
    work_queue.count = 0;
    work_queue.shutdown = 0;
    work_queue.active_threads = 0;
    pthread_mutex_init(&work_queue.mutex, NULL);
    pthread_cond_init(&work_queue.cond, NULL);
}

void work_queue_shutdown() {
    pthread_mutex_lock(&work_queue.mutex);
    work_queue.shutdown = 1;
    pthread_cond_broadcast(&work_queue.cond);
    pthread_mutex_unlock(&work_queue.mutex);
}

void work_queue_add_task(ThreadData* task) {
    pthread_mutex_lock(&work_queue.mutex);
    work_queue.tasks[work_queue.count++] = task;
    pthread_cond_signal(&work_queue.cond);
    pthread_mutex_unlock(&work_queue.mutex);
}

ThreadData* work_queue_get_task() {
    pthread_mutex_lock(&work_queue.mutex);
    while (work_queue.count == 0 && !work_queue.shutdown) {
        pthread_cond_wait(&work_queue.cond, &work_queue.mutex);
    }
    
    if (work_queue.shutdown && work_queue.count == 0) {
        pthread_mutex_unlock(&work_queue.mutex);
        return NULL;
    }
    
    ThreadData* task = work_queue.tasks[--work_queue.count];
    work_queue.active_threads++;
    pthread_mutex_unlock(&work_queue.mutex);
    return task;
}

void work_queue_task_done() {
    pthread_mutex_lock(&work_queue.mutex);
    work_queue.active_threads--;
    if (work_queue.active_threads == 0 && work_queue.count == 0) {
        pthread_cond_signal(&work_queue.cond);
    }
    pthread_mutex_unlock(&work_queue.mutex);
}

int alphaBeta(int depth, int nodeIndex, int isMax, int* scores, 
             int alpha, int beta, int h, int parallel_depth) {
    if (depth == h) {
        return scores[nodeIndex];
    }

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 2; i++) {
            int val;
            if (depth < parallel_depth) {
                ThreadData* task = malloc(sizeof(ThreadData));
                task->depth = depth+1;
                task->nodeIndex = nodeIndex*2+i;
                task->isMax = 0;
                task->scores = scores;
                task->alpha = alpha;
                task->beta = beta;
                task->h = h;
                task->result = 0;
                task->result_ready = 0;
                pthread_mutex_init(&task->result_mutex, NULL);
                pthread_cond_init(&task->result_cond, NULL);
                
                work_queue_add_task(task);
                
                pthread_mutex_lock(&task->result_mutex);
                while (!task->result_ready) {
                    pthread_cond_wait(&task->result_cond, &task->result_mutex);
                }
                val = task->result;
                pthread_mutex_unlock(&task->result_mutex);
                
                pthread_mutex_destroy(&task->result_mutex);
                pthread_cond_destroy(&task->result_cond);
                free(task);
            } else {
                val = alphaBeta(depth+1, nodeIndex*2+i, 0, scores, alpha, beta, h, parallel_depth);
            }
            
            best = (val > best) ? val : best;
            alpha = (best > alpha) ? best : alpha;
            if (beta <= alpha) {
                printf("Pruned at depth %d\n", depth);
                break;
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 2; i++) {
            int val;
            if (depth < parallel_depth) {
                ThreadData* task = malloc(sizeof(ThreadData));
                task->depth = depth+1;
                task->nodeIndex = nodeIndex*2+i;
                task->isMax = 1;
                task->scores = scores;
                task->alpha = alpha;
                task->beta = beta;
                task->h = h;
                task->result = 0;
                task->result_ready = 0;
                pthread_mutex_init(&task->result_mutex, NULL);
                pthread_cond_init(&task->result_cond, NULL);
                
                work_queue_add_task(task);
                
                pthread_mutex_lock(&task->result_mutex);
                while (!task->result_ready) {
                    pthread_cond_wait(&task->result_cond, &task->result_mutex);
                }
                val = task->result;
                pthread_mutex_unlock(&task->result_mutex);
                
                pthread_mutex_destroy(&task->result_mutex);
                pthread_cond_destroy(&task->result_cond);
                free(task);
            } else {
                val = alphaBeta(depth+1, nodeIndex*2+i, 1, scores, alpha, beta, h, parallel_depth);
            }
            
            best = (val < best) ? val : best;
            beta = (best < beta) ? best : beta;
            if (beta <= alpha) {
                printf("Pruned at depth %d\n", depth);
                break;
            }
        }
        return best;
    }
}

void* worker_thread(void* arg) {
    while (1) {
        ThreadData* task = work_queue_get_task();
        if (task == NULL) break;
        
        task->result = alphaBeta(task->depth, task->nodeIndex, task->isMax, 
                               task->scores, task->alpha, task->beta, task->h, 
                               MAX_PARALLEL_DEPTH);
        
        pthread_mutex_lock(&task->result_mutex);
        task->result_ready = 1;
        pthread_cond_signal(&task->result_cond);
        pthread_mutex_unlock(&task->result_mutex);
        
        work_queue_task_done();
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    int num_threads = DEFAULT_NUM_THREADS;
    int tree_size = DEFAULT_TREE_SIZE;
    
    if (argc > 1) tree_size = atoi(argv[1]);
    if (argc > 2) num_threads = atoi(argv[2]);
    
    if (num_threads > MAX_THREADS) num_threads = MAX_THREADS;
    
    int h = 0;
    int nodes = 1;
    while (nodes < tree_size) {
        h++;
        nodes *= 2;
    }
    tree_size = nodes;

    int* scores = malloc(tree_size * sizeof(int));
    generate_scores(scores, tree_size);

    printf("First 5 scores: ");
    for (int i = 0; i < 5 && i < tree_size; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n");

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    work_queue_init();

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, worker_thread, NULL);
    }

    int optimal_value;
    if (h > 0) {
        optimal_value = alphaBeta(0, 0, 1, scores, INT_MIN, INT_MAX, h, MAX_PARALLEL_DEPTH);
    } else {
        optimal_value = scores[0];
    }

    pthread_mutex_lock(&work_queue.mutex);
    while (work_queue.active_threads > 0 || work_queue.count > 0) {
        pthread_cond_wait(&work_queue.cond, &work_queue.mutex);
    }
    pthread_mutex_unlock(&work_queue.mutex);

    work_queue_shutdown();
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + 
                       (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Optimal value: %d\n", optimal_value);
    printf("Time taken: %.6f seconds\n", time_taken);
    printf("Threads used: %d\n", num_threads);

    free(scores);
    pthread_mutex_destroy(&work_queue.mutex);
    pthread_cond_destroy(&work_queue.cond);
    return 0;
}
