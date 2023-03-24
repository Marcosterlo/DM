#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {

  double factors[2];
  double result = 0;

  // Print command
  printf("Command: %s\n", argv[0]);

  // Check of num of arguments

  if (argc != 3) {
    fprintf(stderr, "I need at least 2 arguments but you gave me %d\n",
            argc - 1); // same output on terminal but also on stderr stream
    // Different ways to manage the error

    // goto end;
    // return 0;
    result = -1;
  }

  // Get factors

  for (unsigned int i = 0; i < 2; i++) {
    factors[i] = atof(argv[i + 1]); // atof -> char to double
  }

  result = factors[0] * factors[1];

  printf("%.2f * %.2f = %.2f\n", factors[0], factors[1], result);

  // end:
  return 0;
}