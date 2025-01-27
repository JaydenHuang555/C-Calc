#ifndef EVAL_H
#define EVAL_H

typedef char byte;

struct node_t {
  byte val;
  struct node_t *next, *prev;
};

#endif
