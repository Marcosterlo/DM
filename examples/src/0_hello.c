#include <stdio.h>
#include <stdlib.h>

// MACRO DEFINITIONS
#define GREET "Hello world!"

// To see preprocess file and see it on vscode: clang -E src/0_hello.c | code -

int main() {
  printf(GREET "\n"); 
  return 0;
}