#include <stdio.h>
#include <stdlib.h>

void array_print(float *a, int n);

float *f1(int n);

void f2(float *a, int n);

void f3(float **a, int n); 

int main() {
  int n = 10; // Size of my array

  // First example
  float *a;
  printf("The address of the pointer a is: %p\n", a);

  // Return pointer array
  printf("\nFunction that returns a pointer *****************\n");
  a = f1(n);
  array_print(a, n);
  printf("The address of the pointer a is: %p\n", a);

  free(a);

  // Second example, pass pointer to the function
  printf("\nFunction that takes pointer as input *****************\n");
  float *b = NULL;
  printf("The address of the pointer b is: %p\n", b);
  f2(b, n);
  // array_print(b, n); this cause segmentation fault because the function just
  // operates in its scope at the location indicated by pointer b without
  // effectively changing the b pointer, so at the exit of the function f2 b
  // remains NULL and the launch of print_array function with a null pointer
  // gives the error
  printf("The address of the pointer b is: %p\n", b);
  free(b);

  // Third example, by using double pointers
  printf("\nFunction that takes double pointer as input *****************\n");

  float *c = NULL;
  printf("The address of the pointer c is: %p\n", c);
  f3(&c, n);
  printf("The address of the pointer c is: %p\n", c);
  array_print(c, n);
  free(c);

  return 0;
}

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
  int i = 0;
  for (i = 0; i < n; i++) {
    a[i] = i;
  }
  return a;
}

void f2(float *a, int n) {
  // Definition
  a = malloc(n * sizeof(float));
  printf("f2(%i) the address of the passed pointer is %p\n", n, a);
  // Value assignment
  int i = 0;
  for (i = 0; i < n; i++) {
    a[i] = i;
  }
  array_print(a, n);
}

void f3(float **a, int n) {
  // Definition
  (*a) = malloc(n * sizeof(float));
  printf("f3(%i) the address of the passed pointer is %p\n", n, a);
  printf("The address of the first pointed element is %p\n", *a);
  // Value assignment
  int i = 0;
  for (i = 0; i < n; i++) {
    (*a)[i] = i;
  }
}