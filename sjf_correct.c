#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int turnaround_time;
    int waiting_time;
};

// Function to sort the processes based on burst time using Selection Sort
void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].burst_time < processes[min_index].burst_time) {
                min_index = j;
            }
        }
        // Swap
        struct Process temp = processes[min_index];
        processes[min_index] = processes[i];
        processes[i] = temp;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst times for each process
    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    // Sort processes based on burst time
    sortProcesses(processes, n);

    // Calculate turnaround time and waiting time for each process
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    printf("\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        // Calculate turnaround time
        processes[i].turnaround_time = total_waiting_time + processes[i].burst_time;
        // Calculate waiting time
        processes[i].waiting_time = total_waiting_time;
        
        // Update total waiting time for next process
        total_waiting_time += processes[i].burst_time;
        
        // Update total turnaround time for calculating averages
        total_turnaround_time += processes[i].turnaround_time;
        
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Calculate total waiting time
    total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }

    // Calculate average waiting and turnaround time
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
