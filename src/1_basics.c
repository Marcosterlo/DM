#include <float.h>
#include <string.h>
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

  /* Short */
  printf("\nShort integers **************************** \n");
  short int my_sint = 10;
  printf("My short int size is: %lu, the range is [%d..%d]\n", sizeof(my_sint),
         SHRT_MIN, SHRT_MAX);

  /* Long, long long */
  long int my_lint = LONG_MAX;
  long long int my_llint = LLONG_MAX;
  printf("My long size is: %lu, the range is [%ld..%ld]\n", sizeof(my_lint),
         LONG_MIN, LONG_MAX);
  printf("My long long size is: %lu, the range is [%lld..%lld]\n",
         sizeof(my_llint), LLONG_MIN, LLONG_MAX);
  // Difference between long and long long depends on platform and not compiler,
  // in linux is the same, in Mac it could be different

  /* Unsigned integers */
  printf("\nUnsigned integers **************************** \n");
  unsigned int my_uint = 347;
  printf("My uint size is: %lu, the range is [0..%u]\n", sizeof(my_uint),
         UINT_MAX);

  /* uint32, uint16, uint8...*/
  printf("\nUnsigned integers pt2 **************************** \n");
  uint16_t my_uint16 = 4564;
  printf("My uint size is: %lu, the range is [0..%u]\n", sizeof(my_uint16),
         UINT16_MAX);

  /* Char */ // Usually the same as uint8_t
  printf("\nChar **************************** \n");
  char my_char = 10; /* a */
  printf("My char size is: %lu, the range is [%d..%u]\n", sizeof(my_char),
         CHAR_MIN, CHAR_MAX);

  printf("\n*************************************************");
  float my_float = piApprox;
  double my_double = piApprox;
  long double my_ldouble = piApprox;

  printf("\nFloat ******************************\n");
  printf("The size of float is %lu, and the range is [%e..%e]\n", sizeof(float),
         FLT_MIN, FLT_MAX);
  printf("Number of digits: %d, epsilon: %e\n", FLT_DIG, FLT_EPSILON);
  printf("My float is: %f\n", my_float);

  printf("\nDouble ******************************\n");
  printf("The size of double is %lu, and the range is [%e..%e]\n",
         sizeof(double), DBL_MIN, DBL_MAX);
  printf("Number of digits: %d, epsilon: %e\n", DBL_DIG, DBL_EPSILON);
  printf("My double is: %f\n", my_double);

  printf("\nLong Double ******************************\n");
  printf("The size of long double is %lu, and the range is [%Le..%Le]\n",
         sizeof(long double), LDBL_MIN, LDBL_MAX);
  printf("Number of digits: %d, epsilon: %Le\n", LDBL_DIG, LDBL_EPSILON);
  printf("My long double is: %Lf\n", my_ldouble);

  // Usually it's better to use float if not strictly required since it require
  // less memory

  /* String */
  printf("\nString ****************************************************\n");
  char my_string[20] = "My string!";
  unsigned char my_chr = 'a';

  printf("My string size is: %lu, the capacity is %lu\n", sizeof(my_string),
         strlen(my_string));

  /* Print the array/string index */
  unsigned int i = 0;
  for (i=0; i<sizeof(my_string); i++) {
    printf("|%2d", i);
  }
  printf("\n");

  /* Print characters */
  for (i=0; i<sizeof(my_string); i++) {
    printf("|%2c", my_string[i] ? my_string[i] : ' ');
  }
  printf("\n");

  /* Print char as HEX */
  for (i=0; i<sizeof(my_string); i++) {
    printf("|%2hhX", my_string[i]);
  }
  printf("\n");

  return 0;
}