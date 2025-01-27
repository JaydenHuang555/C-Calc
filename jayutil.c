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

static double stod(const char *str) {
    double result = 0.0, fraction = 0.0, divisor = 0;
    int is_negative = 0, is_fraction = 0;

    if (str == NULL) {
        return 0.0;
    }

    while (*str == ' ' || *str == '\t') {
        str++;
    }

    if (*str == '-') {
        is_negative = 1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            if (is_fraction) {
                fraction += (*str - '0') / divisor;
                divisor *= 10.0;
            } else {
                result = result * 10.0 + (*str - '0');
            }
        } else if (*str == '.') {
            if (is_fraction) {
                break;
            }
            is_fraction = 1;
        } else {
            break;
        }
        str++;
    }

    result += fraction;

    if (is_negative) {
        result = -result;
    }

    return result;
}

struct jayutil_t jayutil = {
    .display_string_array = display_string_array,
    .len = len,
    .memset = memset,
    .stod = stod
};
