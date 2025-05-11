#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <stdatomic.h>

#define MAX_DEPTH 6
#define NUM_THREADS 4  // Adjust based on Grid5000 node cores

typedef struct {
    int value;
    int move;
} ThreadResult;

typedef struct {
    int depth;
    int alpha;
    int beta;
    int player;  // 1 for maximizing, -1 for minimizing
    ThreadResult *result;
    atomic_int *best_move;
    atomic_int *best_score;
} ThreadArgs;

// Simulated game evaluation (replace with actual game logic)
int evaluate_position() {
    return rand() % 100 - 50;  // Random score for demo
}

// Simulate possible moves (replace with actual move generator)
int get_possible_moves(int *moves) {
    int num_moves = 5;  // Example: 5 possible moves
    for (int i = 0; i < num_moves; i++) {
        moves[i] = i;
    }
    return num_moves;
}

// Recursive Alpha-Beta function
int alpha_beta(int depth, int alpha, int beta, int player) {
    if (depth == 0) {
        return evaluate_position();
    }

    int moves[10];
    int num_moves = get_possible_moves(moves);

    if (player == 1) {  // Maximizing player
        int value = INT_MIN;
        for (int i = 0; i < num_moves; i++) {
            int eval = alpha_beta(depth - 1, alpha, beta, -1);
            value = (eval > value) ? eval : value;
            alpha = (alpha > value) ? alpha : value;
            if (alpha >= beta) break;  // Beta cutoff
        }
        return value;
    } else {  // Minimizing player
        int value = INT_MAX;
        for (int i = 0; i < num_moves; i++) {
            int eval = alpha_beta(depth - 1, alpha, beta, 1);
            value = (eval < value) ? eval : value;
            beta = (beta < value) ? beta : value;
            if (beta <= alpha) break;  // Alpha cutoff
        }
        return value;
    }
}

// Thread worker function (parallel search at root)
void *thread_worker(void *args) {
    ThreadArgs *targs = (ThreadArgs *)args;
    int moves[10];
    int num_moves = get_possible_moves(moves);

    for (int i = 0; i < num_moves; i++) {
        int eval = alpha_beta(targs->depth - 1, targs->alpha, targs->beta, -1);

        if (targs->player == 1) {  // Maximizing player
            if (eval > targs->result->value) {
                targs->result->value = eval;
                targs->result->move = i;
            }
        } else {  // Minimizing player
            if (eval < targs->result->value) {
                targs->result->value = eval;
                targs->result->move = i;
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    ThreadResult thread_results[NUM_THREADS];

    // Initialize best score and move (atomic for thread safety)
    atomic_int best_score = INT_MIN;
    atomic_int best_move = -1;

    // Split work among threads
    int moves[10];
    int num_moves = get_possible_moves(moves);
    int moves_per_thread = (num_moves + NUM_THREADS - 1) / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].depth = MAX_DEPTH;
        thread_args[i].alpha = INT_MIN;
        thread_args[i].beta = INT_MAX;
        thread_args[i].player = 1;  // Maximizing player
        thread_args[i].result = &thread_results[i];
        thread_args[i].best_move = &best_move;
        thread_args[i].best_score = &best_score;

        pthread_create(&threads[i], NULL, thread_worker, &thread_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        if (thread_results[i].value > best_score) {
            best_score = thread_results[i].value;
            best_move = thread_results[i].move;
        }
    }

    printf("Best move: %d, Best score: %d\n", best_move, best_score);
    return 0;
}