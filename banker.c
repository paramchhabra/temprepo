#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int n, m;  // Number of processes (n) and resources (m)
int available[MAX_RESOURCES];
int maxMatrix[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Initialize work with available resources
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if (i < n - 1) printf(" -> ");
    }
    printf("\n");
    return true;
}

bool requestResources(int processId, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[processId][i]) {
            printf("Request cannot be granted. Exceeds maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Request cannot be granted. Not enough available resources.\n");
            return false;
        }
    }

    // Tentatively allocate resources
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[processId][i] += request[i];
        need[processId][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request can be granted. The system is in a safe state.\n");
        return true;
    } else {
        // Rollback allocation
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[processId][i] -= request[i];
            need[processId][i] += request[i];
        }
        printf("Request cannot be granted. The system would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    printf("Number of processes: ");
    scanf("%d", &n);
    printf("Number of resource types: ");
    scanf("%d", &m);

    printf("Available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maxMatrix[i][j]);
            need[i][j] = maxMatrix[i][j];  // Initially need = max
        }
    }

    printf("Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];  // Calculate need matrix
        }
    }

    int processId;
    int request[MAX_RESOURCES];
    printf("Request for process: ");
    scanf("%d", &processId);
    printf("Enter request vector: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    requestResources(processId, request);

    return 0;
}
