#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int *queue;
int front = -1;
int rear = -1;

void initializequeue(int size) { queue = (int *)malloc(sizeof(int)); }

void enqueue(int item, int size) {
  if ((rear + 1) % size == front) {
    printf("Queue is full.\n");
    return;
  }
  if (front == -1)
    front = 0;
  rear = (rear + 1) % size;
  queue[rear] = item;
}

int dequeue(int size) {
  if (front == -1) {
    printf("Queue is empty.\n");
    return -1;
  }
  int item = queue[front];
  if (front == rear)
    front = rear = -1;
  else
    front = (front + 1) % size;
  return item;
}

int main() {
  int size = MAX_SIZE;
  initializequeue(size);
  printf("Enqueing elements in the circular queue: \n");
  enqueue(10, size);
  printf("Enqueued 10.\n");
  enqueue(20, size);
  printf("Enqueued 20.\n");
  enqueue(30, size);
  printf("Enqueued 30.\n");
  printf("\n");
  printf("dequeueing elements from the circular queue: \n");
  printf("Dequeued element from the circular queue: %d\n", dequeue(size));
  printf("Dequeued element from the circular queue: %d\n", dequeue(size));
  printf("Dequeued element from the circular queue: %d\n", dequeue(size));
  free(queue);
  return 0;
}