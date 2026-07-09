#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int deque[MAX_SIZE];
int front = -1;
int rear = -1;

void enqueuefront(int item) {
  if (front == -1)
    front = rear = 0;
  else if (front == 0)
    front = MAX_SIZE - 1;
  else
    front--;
  deque[front] = item;
}

void enqueuerear(int item) {
  if (front == -1)
    front = rear = 0;
  else if (rear == MAX_SIZE - 1)
    rear = 0;
  else
    rear++;
  deque[rear] = item;
}

int dequeuefront() {
  if (front == -1) {
    printf("Deque is empty.\n");
    return -1;
  }
  int item = deque[front];
  if (front == rear)
    front = rear = -1;
  else if (front == MAX_SIZE - 1)
    front = 0;
  else
    front++;
  return item;
}

int dequeuerear() {
  if (front == -1) {
    printf("Deque is empty.\n");
    return -1;
  }
  int item = deque[rear];
  if (front == rear)
    front = rear = -1;
  else if (rear == 0)
    rear = MAX_SIZE - 1;
  else
    rear--;
  return item;
}

int main() {
  printf("Enqueing elements in deque: \n");
  enqueuerear(10);
  printf("Enqueued 10 to rear.\n");
  enqueuefront(20);
  printf("Enqueued 20 to front.\n");
  enqueuerear(30);
  printf("Enqueued 30 to rear.\n");
  enqueuefront(40);
  printf("Enqueued 40 to front.\n");
  printf("\n");
  printf("dequeueing: \n");
  printf("Dequeued element from front: %d\n", dequeuefront());
  printf("Dequeued element from rear: %d\n", dequeuerear());
  printf("Dequeued element from front: %d\n", dequeuefront());
  printf("Dequeued element from rear: %d\n", dequeuerear());
  return 0;
}