#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>

int main() {
    int returnstatus;
    int pid;

    // Create pipes
    int size_pipe[2];
    int arr_pipe[2];
    int result_pipe[2];

    if (pipe(size_pipe) == -1 || pipe(arr_pipe) == -1 || pipe(result_pipe) == -1) {
        printf("Unable to create pipes\n");
        return -1;
    }

    // Create process
    pid = fork();
    if (pid == -1) {
        printf("Unable to create the process\n");
        return -1;
    }

    if (pid == 0) { // Child process
        close(size_pipe[1]); // Close write end of size pipe in child
        close(arr_pipe[1]);  // Close write end of array pipe in child
        close(result_pipe[0]); // Close read end of result pipe in child
        
        int size;
        read(size_pipe[0], &size, sizeof(size)); // Read size of array from size pipe
        int num_arr[size];
        read(arr_pipe[0], num_arr, sizeof(num_arr)); // Read array from array pipe

        int sum = 0;
        // Calculate sum of array elements
        for (int i = 0; i < size; i++) {
            sum += num_arr[i];
        }

        // Write sum to result pipe
        write(result_pipe[1], &sum, sizeof(sum));
        
        // Close pipes in child process
        close(size_pipe[0]);
        close(arr_pipe[0]);
        close(result_pipe[1]);
    } else { // Parent process
        close(size_pipe[0]); // Close read end of size pipe in parent
        close(arr_pipe[0]);  // Close read end of array pipe in parent
        close(result_pipe[1]); // Close write end of result pipe in parent

        int size;
        printf("Enter number of elements in array: ");
        scanf("%d", &size);

        int num_arr[size];
        printf("Enter the numbers to add: ");
        for (int i = 0; i < size; i++) {
            scanf("%d", &num_arr[i]);
        }

        // Write size and array to pipes
        write(size_pipe[1], &size, sizeof(size));
        write(arr_pipe[1], num_arr, sizeof(num_arr));

        // Read sum from result pipe
        int sum;
        read(result_pipe[0], &sum, sizeof(sum));
        
        // Display result
        printf("The sum is %d\n", sum);

        // Close pipes in parent process
        close(size_pipe[1]);
        close(arr_pipe[1]);
        close(result_pipe[0]);

        // Wait for child process to terminate
        wait(NULL);
    }
    return 0;
}