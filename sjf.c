#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;
    int completed;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        	processes[i].id = i + 1;
        	processes[i].completed = 0;
        	printf("Process %d:\n", processes[i].id);
        	printf("Arrival Time: ");
        	scanf("%d", &processes[i].arrival_time);
        	printf("Burst Time: ");
        	scanf("%d", &processes[i].burst_time);
        	processes[i].remaining_time = processes[i].burst_time;
    }

    int current_time = 0;
    int completed_processes = 0;

    printf("\nGantt Chart:\n");
    printf("-----------------------------------------------------\n");

    while (completed_processes < n) {
        int min_remaining_time = 9999;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (processes[i].remaining_time < min_remaining_time) {
                    min_remaining_time = processes[i].remaining_time;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            printf("| Idle ");
            current_time++;
        } else {
            processes[selected_process].remaining_time--;
            current_time++;
            printf("| P%d ", processes[selected_process].id);
            if (processes[selected_process].remaining_time == 0) {
                completed_processes++;
                processes[selected_process].completed = 1;
                processes[selected_process].finish_time = current_time;
                processes[selected_process].waiting_time = processes[selected_process].finish_time - processes[selected_process].arrival_time - processes[selected_process].burst_time;
                processes[selected_process].turnaround_time = processes[selected_process].finish_time - processes[selected_process].arrival_time;
            }
        }
    }

    printf("|\n");
    printf("-----------------------------------------------------\n");

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

