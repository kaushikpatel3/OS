#include <stdio.h>

struct Process {
    int id, st, wt, ft, at, bt, tt, c, rt;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: \n");
    scanf("%d", &n);
    printf("Enter the time quantum: \n");
    scanf("%d", &quantum);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].c = 0;
        printf("\nProcess %d:\n", processes[i].id);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].at);
        printf("Burst Time: ");
        scanf("%d", &processes[i].bt);
        processes[i].rt = processes[i].bt;
    }

    int ct = 0, cp = 0;
    int time_quantum = 0;

    printf("\nGantt Chart: ");
    while (cp < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= ct && processes[i].rt > 0) {
                found = 1;
                if (processes[i].rt > quantum) {
                    printf(" P%d |", processes[i].id);
                    ct += quantum;
                    processes[i].rt -= quantum;
                } else {
                    printf(" P%d |", processes[i].id);
                    ct += processes[i].rt;
                    processes[i].rt = 0;
                    cp++;
                    processes[i].ft = ct;
                    processes[i].wt = processes[i].ft - processes[i].at - processes[i].bt;
                    processes[i].tt = processes[i].wt + processes[i].bt;
                }
            }
        }
        if (!found) {
            printf(" idle |");
            ct++;
        }
    }
    printf("\n\n");

    printf("\nProcess\tArrival Time\tBurst time\tWaiting Time\tTurnaround time");
    int twt = 0, ttt = 0;

    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d", processes[i].id, processes[i].at, processes[i].bt, processes[i].wt,
               processes[i].tt);
        twt += processes[i].wt;
        ttt += processes[i].tt;
    }

    float awt, att;
    awt = (float) twt / n;
    att = (float) ttt / n;

    printf("\n\nAWT: %f", awt);
    printf("\nATT: %f", att);
    return 0;
}

