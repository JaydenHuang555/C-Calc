#ifndef STACK_H
#define STACK_H
#include "common.h"

struct stack_t {
  void (*construct)(void);
  void (*push)(byte *element);
  byte *(*peek)(void);
  byte *(*pop)(void);
  int (*is_empty)(void);
};

extern struct stack_t stack;

#endif
