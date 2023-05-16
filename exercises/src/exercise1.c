#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 300

int main(int argc, char *argv[]) {
  FILE *old = NULL, *new = NULL;
  char *name = NULL, *tmp = NULL;
  char last = 0;
  size_t n = 0;
  ssize_t nread = 0;
  int incr = 0, n_actual = 0;
  char *buffer = malloc(MAX_LENGTH);

  if (argc != 3) {
    printf("Exactly 2 argument must be passed: gcode file name and increment\n");
    return 1;
  } else {
    printf("Passed name file: %s\n", argv[1]);
    name = argv[1];
    printf("Passed increment: %d\n", atoi(argv[2]));
    incr = atoi(argv[2]);
  }
  
  old = fopen(name, "r");
  new = fopen("new.gcode", "w");

  if (!old) {
    printf("File not opened correctly\n");
    goto fail;
  }
  else if (!new) {
    printf("New file not opened correctly\n");
    goto fail;
  }
  else {
    printf("File aperti correttamente\n");
  }

  // Parsing
  while ((nread = getline(&buffer, &n, old)) != -1) {
    if (!strcmp(buffer, "\n")) {
      continue;
    }
    if (buffer[strlen(buffer) - 1] != '\n') {
      last = 1;
    }
    while ((tmp = strsep(&buffer, " "))) {
      tmp[0] = toupper(tmp[0]);
      switch (tmp[0])
      {
      case 'N':
        fprintf(new, "N%04d", n_actual);
        n_actual += incr;
        break;
      default:
        fprintf(new, " %s", tmp);
        break;
      }
    }
    if (last) {
      fprintf(new, "\n");
    }
  }
  fprintf(new, "\n");

fail:
  free(buffer);
  if (new)
    fclose(new);
  if (old)
    fclose(old);
  return 0;
}