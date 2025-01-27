#include "eval.h"
#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "jayutil.h"

int prec(byte c){
  switch(c){
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
    case '%':
      return 2;
    case '(':
    case ')':
      return -1;
    default: return 0;
  }
}

byte *stringize(byte c){
  switch(c){
    case '+': return "+";
    case '-': return "-";
    case '*': return "*";
    case '/': return "/";
    case '%': return "%";
    case '(': return "(";
    case ')': return ")";
    default: return 0;
  }
}

int is_num(byte c){
  return (('0' - 1) < c && c < ('9' + 1)) || c == '.';
}

#define BUILDER_ISEMPTY() ((builder_info.off == 0))
#define DIGESTED_ISEMPTY() ((digested_info.off == 0))

struct info_t {
  size_t off, len;
};

struct info_t 
  builder_info = {
    .off = 0,
    .len = 1 << 3
  },
  digested_info = {
    .off = 0,
    .len = 1 << 3
  };

byte **digested, *builder;

void digested_add(byte *item){
  assert(item && "attempted to digested a null string");
  digested[digested_info.off++] = item;
  if(digested_info.off == digested_info.len){
    byte **next = (byte**)malloc(sizeof(byte*) * (digested_info.len *= 2));
    for(int i = 0; i < digested_info.len; i++)
      next[i] = i / 2 > digested_info.len ? digested[i] : 0;
    free(digested);
    digested = next;
  }
}

void builder_add(byte c){
  assert(c && "attempted to build with a null char");
  builder[builder_info.off++] = c;
  if(builder_info.len == builder_info.off){
    byte *next = (byte*)malloc(builder_info.len *= 2);
    for(int i = 0; i < builder_info.len; i++)
      next[i] = i / 2 > builder_info.len ? builder[i] : 0;
    free(builder);
    builder = next;
  }
}

void init(void){
  builder_info.off = 0;
  builder_info.len = 1 << 3;

  digested_info.off = 0;
  digested_info.len = 1 << 3;

  digested = (byte**)malloc(sizeof(byte*) * digested_info.len);
  builder = (byte*)malloc(builder_info.len);

  jayutil.memset(digested, 0, digested_info.len * sizeof(byte*));
  jayutil.memset(builder, 0, builder_info.len);

}


double eval(byte *equation){
  init();
  stack.construct();
  for(int i = 0; i < jayutil.len(equation); i++){
    byte c = equation[i];
    int JJ = 0;
    if(prec(c)){
      if(!BUILDER_ISEMPTY()){
        digested_add(builder);
        builder_info.len = 1 << 3;
        builder_info.off = 0;
        builder = (byte*)malloc(builder_info.len);
        jayutil.memset(builder, 0, builder_info.len);
      }
      if(BUILDER_ISEMPTY() && c == '-'){
        JJ = 1;
        builder_add('-');
      }
      if(!JJ)
      switch(c){
        case '(':
          stack.push(")");
          break;
        case ')':
          while(!stack.is_empty() && *stack.peek() != '(') digested_add(stack.pop());
          break;
        default:
          while(!stack.is_empty() && prec(*stack.pop()) > prec(c)) digested_add(stack.pop());
          stack.push(stringize(c));
          break;
      }
    }
    if(is_num(c)) builder_add(c);
  }
  if(!BUILDER_ISEMPTY()) digested_add(builder);
  while(!stack.is_empty()) digested_add(stack.pop());

  jayutil.display_string_array((const byte**)digested, digested_info.off);

  for(int i = 0; i < digested_info.off; i++){
    byte *token = digested[i];
    if(is_num(token[jayutil.len(token) - 1])) stack.push(token);
    if(prec(token[jayutil.len(token) - 1])){
      double left, right;
      byte *left_b, *right_b, *buffer;
      right_b = stack.pop();
      left_b = stack.pop();

      right = strtod(right_b, &buffer);
      left = strtod(left_b, &buffer);

      double total = 0;
      byte buff[sizeof(double) + 1];
      jayutil.memset(buff, 0, sizeof(double));
      switch(*token){
        case '+':
          total = left + right;
          break;
        case '-':
          total = left - right;
          break;
        case '*':
          total = left * right;
          break;
        case '/':
          total = left / right;
          break;
        case '%':
          total = (long long)left % (long long)right;
          break;
        default:
          total = 0;
          assert(total && "invalid operator parsed");
          break;
      }
      sprintf(buff, "%f", total);
      stack.push(buff);
    }
  }

  byte *K;
  double ret = strtod(stack.pop(), &K);
  for(int i = 0; i < digested_info.off; i++){
    byte *c = digested[i];
    if(!prec(c[jayutil.len(c) - 1])) free(c);
  } 

  if(digested) free(digested);
  return ret;
}

#define EXIT_CMD "exit"

int main(int argc, byte **argv){
  while(1 == 1){
    printf("please enter an equation: ");
    byte buff[1024];
    jayutil.memset(buff, 0, sizeof(buff));
    fgets(buff, sizeof(buff), stdin);
    if(jayutil.cmp(buff, EXIT_CMD) == 0) return 0;
    else printf("%f\n", eval(buff));
  }
  return 0;
}
