#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int queue[MAX_SIZE];
int front = -1;
int rear = -1;

void enqueue(int item) {
  if (rear == MAX_SIZE - 1) {
    printf("Queue is full.\n");
    return;
  }
  if (front = -1)
    front = 0;
  queue[++rear] = item;
}

int dequeue() {
  if (front == -1) {
    printf("Queue is empty.\n");
    return -1;
  }
  int item = queue[front++];
  if (front > rear)
    front = rear = -1;
  return item;
}

int main() {
  printf("Enqueing elements in the array: \n");
  enqueue(10);
  printf("Enqueued 10.\n");
  enqueue(20);
  printf("Enqueued 20.\n");
  enqueue(30);
  printf("Enqueued 30.\n");
  printf("\n");
  printf("dequeueing elements from the array: \n");
  printf("Dequeued element from the array: %d\n", dequeue());
  printf("Dequeued element from the array: %d\n", dequeue());
  printf("Dequeued element from the array: %d\n", dequeue());
  return 0;
}