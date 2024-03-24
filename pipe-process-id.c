#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n; // Number of times to call fork
    printf("Enter the number of times to call fork: ");
    scanf("%d", &n);

    printf("Parent process ID: %d\n", getpid());
    printf("Number of times fork will be called: %d\n", n);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork failed\n");
            return 1;
        } else if (pid == 0) {
            // Child process
            printf("Child process ID: %d, Parent process ID: %d\n", getpid(), getppid());
            break; // Child process doesn't fork further
        } else {
            // Parent process
            wait(NULL); // Wait for child process to complete
        }
    }

    return 0;
}
