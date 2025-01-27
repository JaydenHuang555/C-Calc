#include "stack.h"
#include "stdlib.h"

struct node {
  byte *val;
  struct node *prev, *next;
};

struct node *head, *tail;

void construct(void){
  head = 0;
  tail = 0;
}


static struct node *nalloc(struct node *next, byte *v){
  next = malloc(sizeof(struct node));
  next->next = 0;
  next->prev = 0;
  next->val = v;
  return next;
}

void push(byte *element){
  if(!head){
    head = nalloc(head, element);
    tail = head;
  }
  else {
    tail->next = nalloc(tail->next, element);
    tail->next->prev = tail;
    tail = tail->next;
  }
}

byte *peek(void){
  return tail->val;
}

byte *pop(void){
  byte *ret = peek();
  if(tail == head){
    free(head);
    head = 0;
    tail = 0;
  }
  else {
    tail = tail->prev;
    free(tail->next);
    tail->next = 0;
  }
  return ret;
}

int is_empty(void){
  return head == 0;
}

struct stack_t stack = {
  .construct = construct,
  .push = push,
  .peek = peek,
  .pop = pop,
  .is_empty = is_empty
};
