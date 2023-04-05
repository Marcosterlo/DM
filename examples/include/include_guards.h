#ifndef INCLUDE_GUARDS_H
#define INCLUDE_GUARDS_H // this is usued to make the compiler compile all the
                         // first time it's included and the second time it will
                         // not compile what's already compiled
#include <stdio.h>
#include <stdlib.h>

// Marco definition
#define TWICE(o) 2 * o // like a function on the go that get substituted

// Function prototypes
void print_arguments(int argc, const char **argv);

// Types (just to give an example)
typedef struct {
  int a;
  double b;
} my_struct_t;

typedef double data_t; // everytime we use data_t we are instead using a double

#endif // INCLUDE_GUARDS_H