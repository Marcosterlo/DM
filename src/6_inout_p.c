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
  printf("The address contained in the pointer a is: %p\n", a);
  // This prints 0x1000, an low address, probably in the stack because
  // intialized in the stack
  printf("The address of pointer to float variable &a is: %p\n", &a);
  // the variable *a is located somewhere in the heap, the value it stores is
  // 0x1000

  // Return pointer array
  printf("\nFunction that returns a pointer *****************\n");
  printf("The address contained in the pointer a is: %p\n", a);
  a = f1(n);
  array_print(a, n);
  printf("The address contained in the pointer a is: %p\n", a);
  printf("The address of pointer to float variable &a is: %p\n", &a);
  // In this case, before the f1 function call, a is generically initialized
  // containing the address 0x1000 and stored in some random location in the
  // heap. f1 returns a float*, assigning a to the return of the function make
  // it store the address created via malloc function inside the function,
  // without changing the place where the float pointer variable a is stored

  free(a);

  // Second example, pass pointer to the function
  printf("\nFunction that takes pointer as input *****************\n");
  float *b = NULL;
  printf("The address contained in the pointer b is: %p\n", b);
  printf("The address of pointer to float variable &b is: %p\n", &b);
  f2(b, n);
  // array_print(b, n); this cause segmentation fault because the function just
  // operates in its scope at the location indicated by pointer b (NULL) without
  // effectively changing the b pointer, so at the exit of the function f2 the
  // value contained in b gets deleted because out of scope and b remains NULL.
  // The launch of print_array function with a null pointer gives the error
  printf("The address contained in the pointer b is: %p\n", b);
  printf("The address of pointer to float variable &b is: %p\n", &b);
  free(b);

  // Third example, by using double pointers
  printf("\nFunction that takes double pointer as input *****************\n");

  float *c = NULL;
  printf("The address contained in the pointer c is: %p\n", c);
  printf("The address of pointer to float variable &c is: %p\n", &c);
  f3(&c, n);
  printf("The address contained in the pointer c is: %p\n", c);
  printf("The address of pointer to float variable &c is: %p\n", &c);
  array_print(c, n);
  free(c);
  // In this case we pass to f3 a double pointer to float, c refers to the
  // pointer stored in c, &c is the address of the pointer variable storage
  // location. We pass to f3 &c: a float **variable, in the function we create
  // in (*c), or in other words just c in the main scope, the address created
  // via malloc where we operate creating an array. At the exit of the function,
  // since we passed a double pointer, c will maintain the value created via
  // malloc in the function, differently from the second case where out of f2
  // scope the value eliminated itself. The original storage location &c in the
  // main scope remains unchanged

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