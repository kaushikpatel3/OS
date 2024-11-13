#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int n, m; // Number of processes and resources

int isSafe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int safeSeq[MAX_PROCESSES];

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("Not in a safe state\n");
            return 0;
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", safeSeq[i]);
    }
    printf("P%d\n", safeSeq[n - 1]);
    return 1;
}

int requestResource(int p, int request[MAX_RESOURCES]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[p][i] || request[i] > available[i]) {
            printf("Request denied. Not safe.\n");
            return 0;
        }
    }

    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    if (isSafe()) {
        printf("Resource request granted.\n");
        printf("Updated allocation matrix:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", allocation[i][j]);
            }
            printf("\n");
        }
        return 1;
    } 
    else {
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }
    }

    printf("Request denied. Not safe.\n");
    return 0;
}

int main() {
    printf("Banker's Algorithm\n");

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Input maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Input allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Input available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    isSafe();

    while (1) {
        int p;
        printf("Enter process requesting resources (0 to %d or -1 to exit): ", n - 1);
        scanf("%d", &p);
        if (p == -1) break;
        if (p < 0 || p >= n) {
            printf("Invalid process number.\n");
            continue;
        }
        int request[MAX_RESOURCES];
        printf("Enter resource request for P%d:\n", p);
        for (int i = 0; i < m; i++) {
            scanf("%d", &request[i]);
        }
        if (requestResource(p, request)) {
            printf("Resource request granted.\n");
        } else {
            printf("Resource request denied.\n");
        }
    }

    return 0;
}

