#ifndef JAYUTIL_H

#define JAYUTIL_H

struct jayutil_t {
  void (*display_string_array)(const char**, unsigned long);
  unsigned long (*len)(void*);
  void *(*memset)(void *, int , unsigned long);
  int (*cmp)(const char*, const char*);
  double (*stod)(const char*);
};

extern struct jayutil_t jayutil;

#endif
