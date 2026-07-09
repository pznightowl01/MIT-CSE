#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
  int item;
  int priority;
} element;

element priorityque[MAX_SIZE];
int size = 0;

void enqueue(element ele) {
  if (size == MAX_SIZE) {
    printf("priority queue is full\n");
    return;
  }
  int i = size - 1;
  while (i > 0 && priorityque[i].priority < ele.priority) {
    priorityque[i + 1] = priorityque[i];
    i--;
  }
  priorityque[i + 1] = ele;
  size++;
}

element dequeue() {
  if (size == 0) {
    printf("priority queue is empty\n");
    element empty = {-1, -1};
    return empty;
  }
  element item = priorityque[size - 1];
  size--;
  return item;
}

int main() {
  printf("Enqueing elements with priorities: \n");
  element ele1 = {10, 5};
  printf("Enqueued 10.\n");
  element ele2 = {20, 1};
  printf("Enqueued 20.\n");
  element ele3 = {30, 2};
  printf("Enqueued 30.\n");
  element ele4 = {40, 3};
  printf("Enqueued 40.\n");
  element ele5 = {50, 4};
  printf("Enqueued 50.\n");
  enqueue(ele1);
  enqueue(ele2);
  enqueue(ele3);
  enqueue(ele4);
  enqueue(ele5);
  printf("\n");
  printf("dequeueing: \n");
  element dequeued1 = dequeue();
  element dequeued2 = dequeue();
  element dequeued3 = dequeue();
  element dequeued4 = dequeue();
  element dequeued5 = dequeue();
  printf("Item: %d, Priority:%d\n", dequeued1.item, dequeued1.priority);
  printf("Item: %d, Priority:%d\n", dequeued2.item, dequeued2.priority);
  printf("Item: %d, Priority:%d\n", dequeued3.item, dequeued3.priority);
  printf("Item: %d, Priority:%d\n", dequeued4.item, dequeued4.priority);
  printf("Item: %d, Priority:%d\n", dequeued5.item, dequeued5.priority);
  return 0;
}