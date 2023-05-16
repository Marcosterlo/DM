#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 300

int main(int argc, char *argv[]) {
  FILE *fp = NULL;
  int nlines = 0, shortest = 0, longest = 0, nchar = 0, nlon = 0,
      nshort = 0;
  char *buffer = malloc(MAX_LENGTH), *name = NULL;
  size_t n = 0;


  if (argc != 2) {
    printf("Only 1 argument should be passed: filename\n");
    return 1;
  }
  name = argv[1];

  fp = fopen(name, "r");

  if (!fp) {
    printf("Could not open file\n");
    return 1;
  }

  while (getline(&buffer, &n, fp) != -1) {

    nlines++;
    nchar += n;

    if (n>nlon) {
      nlon = n;
      longest = nlines;
    }

    if (n<nshort) {
      nshort = n;
      shortest = nlines;
    }

  }

  printf("Number of lines: %d\n", nlines);
  printf("Number of char: %d\n", nchar);
  printf("Index of longest line: %d\n", longest);
  printf("Length of longest line: %d\n", nlon);
  printf("Index of shortest line: %d\n", shortest);
  printf("Length of shortest line: %d\n", nshort);


  if (fp) {
    fclose(fp);
  }
  if (buffer) {
    free(buffer);
  }

  return 0;
}