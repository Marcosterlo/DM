#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

enum errors {
  ERRORS_SUCCESS = 100,
  ERRORS_OPEN,
  ERRORS_READ,
  ERRORS_WRITE,
  ERRORS_ARGS
};

typedef enum errors errors_t;

int main(int argc, const char **argv) {
  errors_t result = ERRORS_SUCCESS;
  const char *filename;

  if (argc != 2) {
    fprintf(stderr, "I have to give me only 2 arguments!\n");
    result = ERRORS_ARGS;
    goto end;
  }

  // Writing a file
  printf("Test file writing! *****************\n");
  { // this defines a scope, all the variables inside here are only accessible
    // inside of it
    filename = argv[1];
    fprintf(stdout, "My filename is %s\n", filename);

    FILE *f = fopen(filename, "w");
    if (!f) {
      fprintf(stderr, "I was not able to open the file!\n");
      result = ERRORS_OPEN;
      goto end;
    }

    fprintf(f, "I'm a line\n");
    fprintf(f, "I'm another line\n");
    fprintf(
        f, "I'm a number %f\n",
        20.0f); // this tells to get 20 as a float and not a double as default

    fclose(f);
  }

  printf("Test file reading! *****************\n");
  {
    char buffer[MAX_LINE_LENGTH];
    FILE *f = fopen(filename, "r");

    if (!f) {
      fprintf(stderr, "I was not able to read the file!\n");
      result = ERRORS_READ;
      goto end;
    }

    while (fgets(buffer, MAX_LINE_LENGTH, f)) { // loop untile file EOF
      fprintf(stdout, "%s", buffer);
    }

    fclose(f);
  }

end:
  return result;
}

// We can redirect the stdout to a file with the terminal operator >. To
// separate different streams like stdout and stderr we can do something like
// this:

// exectutablefile [arguments] > stdout.log 2> error.log