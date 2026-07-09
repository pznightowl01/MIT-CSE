#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int alloc[P][R], max[P][R], need[P][R], avail[R];

void calcNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafe() {
    int work[R], finish[P] = {0}, safeSeq[P], count = 0;
    for (int i = 0; i < R; i++) work[i] = avail[i];

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAlloc = true;
                for (int j = 0; j < R; j++)
                    if (need[i][j] > work[j]) canAlloc = false;
                if (canAlloc) {
                    for (int j = 0; j < R; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

bool request(int pid, int req[]) {
    for (int i = 0; i < R; i++) {
        if (req[i] > need[pid][i]) return printf("Error: exceeds maximum claim.\n"), false;
        if (req[i] > avail[i]) return printf("Not enough resources available.\n"), false;
    }
    for (int i = 0; i < R; i++) {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
    }
    if (isSafe()) return printf("Request granted.\n"), true;

    for (int i = 0; i < R; i++) {
        avail[i] += req[i];
        alloc[pid][i] -= req[i];
        need[pid][i] += req[i];
    }
    printf("Request leads to UNSAFE state. Rolled back.\n");
    return false;
}

int main() {
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < R; i++) scanf("%d", &avail[i]);

    calcNeed();
    if (!isSafe()) printf("System is NOT in a safe state.\n");

    int pid, req[R];
    printf("\nEnter process ID and request (A B C): ");
    scanf("%d", &pid);
    for (int i = 0; i < R; i++) scanf("%d", &req[i]);
    request(pid, req);
    return 0;
}
