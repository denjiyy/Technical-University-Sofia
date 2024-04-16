#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int success_count = 0;
    int error_count = 0;

    for (int i = 1; i < argc; i++) {
        int pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            execlp(argv[i], argv[i], NULL);
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
        else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                success_count++;
            }
            else {
                error_count++;
            }
        }
    }

    printf("Successful commands: %d\n", success_count);
    printf("Commands that have ended with an error: %d\n", error_count);

    return 0;
}
