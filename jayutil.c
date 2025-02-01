#include "jayutil.h"
#include "stdio.h"

typedef char byte;

static void display_string_array(const byte **cc, unsigned long len){
  printf("{ ");
  for(unsigned long i = 0; i < len; i++)
    printf("%s, ", cc[i]);
  printf("\b\b }\n");
}

static unsigned long len(void *s){
  byte *c = (byte*)s;
  while(*c) c++;
  return (unsigned long)(c - (byte*)s);
}

static void *memset(void *buff, int c, unsigned long s){
  byte *buffer = (byte*)buff;
  for(int i = 0; i < s; i++) buffer[i] = c;
  return buff;
}

static double stod(const byte *input){
  size_t integerPlaces = 0, decimalPlaces = 0, isPassedDecimal = 0;
  for(int i = 0; i < len((void*)input); i++){ 
    if(input[i] != '.') integerPlaces++;
    if(isPassedDecimal) decimalPlaces++;
    else if(input[i] == '.') isPassedDecimal = 1;
  }
  double ret = 0;
  int i = len((void*)input);
  isPassedDecimal = 0;
  for(;i != 0;){
    
    --i;
  }
  fprintf(stderr, "method is not done \n");
  return ret;
}

int cmp(const byte *cc, const byte *bb){
  byte *c = (byte*)cc, *b = (byte*)bb;
  while(*c && *b){
    if(*(c++) != *(b++)) break;
  }
  return (*c - *b);
}

struct jayutil_t jayutil = {
    .display_string_array = display_string_array,
    .len = len,
    .memset = memset,
    .cmp = cmp,
    .stod = stod
};
