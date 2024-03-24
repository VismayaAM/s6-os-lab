#include <stdio.h>

int main() {
    // Matrix for storing Process Id, Burst Time, Arrival Time, Waiting Time, and Turnaround Time.
    int A[100][5];
    int i, j, n, total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time and Arrival Time for each process:\n");
    // User Input Burst Time and Arrival Time and alloting Process Id.
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &A[i][1], &A[i][2]); // Burst Time and Arrival Time
        A[i][0] = i + 1; // Process ID
    }

    // Sorting processes according to their Arrival Time.
    for (i = 0; i < n; i++) {
        int index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][2] < A[index][2]) {
                index = j;
            }
        }
        // Swapping Process ID, Burst Time, and Arrival Time
        int temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;

        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        temp = A[i][2];
        A[i][2] = A[index][2];
        A[index][2] = temp;
    }

    // Calculation of Waiting Times and Turnaround Times
    for (i = 0; i < n; i++) {
        A[i][3] = (i == 0) ? 0 : A[i - 1][3] + A[i - 1][1]; // Waiting Time
        A[i][4] = A[i][3] + A[i][1]; // Turnaround Time
        total_wt += A[i][3]; // Total Waiting Time
        total_tat += A[i][4]; // Total Turnaround Time
    }

    // Printing the details and calculations
    printf("P   AT   BT   WT   TAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d   %d    %d    %d    %d\n", A[i][0], A[i][2], A[i][1], A[i][3], A[i][4]);
    }

    // Calculating and printing Average Waiting Time and Average Turnaround Time
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average Waiting Time= %f\n", avg_wt);
    printf("Average Turnaround Time= %f\n", avg_tat);

    return 0;
}