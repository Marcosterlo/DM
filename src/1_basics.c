#include <float.h>
#include <limits.h> // tells properties about types and variables
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const double piApprox = 3.14159;
#define PI_APPROX 3.14159L
#define MAX_ARR_SIZE 1000U
// stands for long double macro definition, U stands for unsigned integer
// There's a particular part dedicated to constant allocation, with the macro
// approach we save a bit of memory because we save space on the variable
// allocation

int main() {
  /* Integers */
  int my_int = INT_MAX;
  printf("My int size is: %lu, the range is [%d..%d]\n", sizeof(int), INT_MIN,
         INT_MAX);

  /* Overflow */
  printf("My int is: %d\n", my_int + 1);

  return 0;
}