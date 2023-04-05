#include "include_guards.h"
#include "include_guards.h" // The whole concept is to avoid inserting the same header file multiple times in the same file. In this example is nonsense but we could for example include header1 and header2 but header2 has already included header1 in its definition, doing so we would include header1 2 times. With the file guards we prevent the behaviour and the conseguent error launch of the pre-processor
#include <stdio.h>
#include <stdlib.h>

// in the main there's print_arguments, since it's not already defined it should
// give error but we included the header file containing the function
// declaration so everything works fine

int main(int argc, const char **argv) {

  // Print all arguments
  print_arguments(argc, argv);

  return 0;
}

void print_arguments(int argc, const char **argv) {

  for (unsigned int i = 1; i < argc; i++) {
    printf("Elem #%d - Content: %s\n", i, argv[i]);
  }
}