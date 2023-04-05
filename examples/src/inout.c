#include "inout.h"

void array_print(float *a, int n) {
  printf("[");
  for (int i = 0; i < n; i++) {
    printf(" %.1f ", a[i]);
  }
  printf("]\n");
}

float *f1(int n) {
  // Definition
  float *a = malloc(n * sizeof(float));
  printf("f1(%i) the value of the pointer is %p\n", n, a);
  // Value assignment
  for (int i = 0; i < n; i++) {
    a[i] = i;
  }
  return a;
}

void f2(float *a, int n) {
  // Definition
  printf("f2(%i) the address of the passed pointer is %p\n", n, a);
  a = malloc(n * sizeof(float));
  printf("f2(%i) the address of the passed pointer after malloc allocation is "
         "%p\n",
         n, a);
  // Value assignment
  for (int i = 0; i < n; i++) {
    a[i] = i;
  }
  array_print(a, n);
}

void f3(float **a, int n) {
  // Definition
  (*a) = malloc(n * sizeof(float));
  printf("f3(%i) the address of the passed pointer is %p\n", n, a);
  printf("f3(%i) the address created via malloc and stored in *c is %p\n", n,
         *a);
  // Value assignment
  for (int i = 0; i < n; i++) {
    (*a)[i] = i;
  }
}