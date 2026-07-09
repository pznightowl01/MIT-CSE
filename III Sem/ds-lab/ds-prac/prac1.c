#include <stdio.h>

struct ListNode{
int data;
struct ListNode* next;
};

int ListLength(struct ListNode *head){
  struct ListNode *curr=head;
  int count=0;

  while(curr!=NULL){
    count++;
    curr=curr->next;
  }
  return count;
}

int main(){
  struct ListNode* head=NULL;
  int length=ListLength(head);
  printf("Length of linked list: %d\n",length);
  return 0;
}