#include <stdio.h>
#include <stdlib.h>

#define MAXP 100
#define TQ 5

typedef struct {
    int id, bt, remt, arrt, qlvl;
} Process;

typedef struct {
    Process *p[MAXP];
    int front, rear;
} Queue;

void init(Queue *q) { q->front = q->rear = -1; }
int empty(Queue *q) { return q->front == -1; }
void enqueue(Queue *q, Process *pr) {
    if (q->rear == MAXP - 1) return;
    if (empty(q)) q->front = 0;
    q->p[++q->rear] = pr;
}
Process* dequeue(Queue *q) {
    if (empty(q)) return NULL;
    Process *pr = q->p[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return pr;
}
Process* createP(int id, int bt, int arrt, int lvl) {
    Process *pr = malloc(sizeof(Process));
    *pr = (Process){id, bt, bt, arrt, lvl};
    return pr;
}

void FCFS(Queue *q) {
    while (!empty(q)) {
        Process *p = dequeue(q);
        printf("P%d (FCFS) executed for %d units\n", p->id, p->remt);
        free(p);
    }
}

void SJF(Queue *q) {
    while (!empty(q)) {
        int min = q->front;
        for (int i = q->front; i <= q->rear; i++)
            if (q->p[i]->remt < q->p[min]->remt) min = i;
        Process *tmp = q->p[q->front]; q->p[q->front] = q->p[min]; q->p[min] = tmp;
        Process *p = dequeue(q);
        printf("P%d (SJF) executed for %d units\n", p->id, p->remt);
        free(p);
    }
}

void RR(Queue *q, Queue *next) {
    while (!empty(q)) {
        Process *p = dequeue(q);
        int run = (p->remt < TQ) ? p->remt : TQ;
        printf("P%d (RR) ran for %d units\n", p->id, run);
        p->remt -= run;
        if (p->remt > 0) {
            p->qlvl++;
            printf("P%d moved to level %d\n", p->id, p->qlvl);
            enqueue(next, p);
        } else {
            printf("P%d completed\n", p->id);
            free(p);
        }
    }
}

int main() {
    Queue q[3]; for (int i = 0; i < 3; i++) init(&q[i]);

    enqueue(&q[0], createP(1, 10, 0, 0));
    enqueue(&q[1], createP(2, 5, 0, 1));
    enqueue(&q[2], createP(3, 8, 0, 2));
    enqueue(&q[2], createP(4, 2, 0, 2));

    printf("Multilevel Feedback Queue Scheduling:\n");

    if (!empty(&q[0])) { printf("\nLevel 0:\n"); FCFS(&q[0]); }
    if (!empty(&q[1])) { printf("\nLevel 1:\n"); SJF(&q[1]); }
    if (!empty(&q[2])) { printf("\nLevel 2:\n"); RR(&q[2], &q[2]); }

    return 0;
}
