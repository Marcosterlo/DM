//   ____
//  |  _ \ _ __ ___   __ _ _ __ __ _ _ __ ___
//  | |_) | '__/ _ \ / _` | '__/ _` | '_ ` _ \ 
//  |  __/| | | (_) | (_| | | | (_| | | | | | |
//  |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|
//                   |___/

#include "program.h"
#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
// #include "defines.h"
// #include "machine.h"

// Object structure:
typedef struct program {
  char *filename;
  FILE *file;
  block_t *first, *current, *last;
  size_t n;
} program_t;

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Lifecycle functions
program_t *program_new(char const *filename) {
  program_t *p = malloc(sizeof(*p));

  if (!p) {
    eprintf("Could not create program\n");
    return NULL;
  }

  if (!filename || strlen(filename) == 0) {
    eprintf("Improper or empty file name\n");
    free(p);
    return NULL;
  }

  // Initialize fields
  p->filename = strdup(filename);
  // If we want to save a string we have to make a copy of it since it's scope
  // it's only inside the function
  p->first = NULL;
  p->current = NULL;
  p->last = NULL;
  p->n = 0;

  return p;
}

void program_free(program_t *p) {
  assert(p);
  block_t *b, *tmp;
  // In order to free a linked list we have to free each block singularly one at
  // a time, we need a temporary block pointer
  if (p->n > 0) {
    b = p->first;
    do {
      tmp = b;
      b = block_next(b);
      // shouldn't we set to NULL b->prev?
      block_free(tmp);
    } while (b);
  }
  free(p->filename);
  free(p);
}

void program_print(program_t const *p, FILE *output) {
  assert(p && output);
  block_t *b = p->first;
  do {
    block_print(b, output);
    b = block_next(b);
  } while (b);
}

// Accessors
#define program_getter(typ, par, name)                                         \
  typ program_##name(program_t const *p) {                                     \
    assert(p);                                                                 \
    return p->par;                                                             \
  }

program_getter(char *, filename, filename);
program_getter(block_t *, first, first);
program_getter(block_t *, current, current);
program_getter(block_t *, last, last);
program_getter(size_t, n, length);

// Processing
int program_parse(program_t *p, machine_t *m) {
  assert(p && m);
  char *line = NULL;
  size_t n = 0;
  // signed size_t (we neeed it signed cause getlinre returns a negative value
  // in case of error)
  ssize_t line_len = 0;
  block_t *b;

  p->file = fopen(p->filename, "r");

  if (!p->file) {
    eprintf("Cannot open the file %s\n", p->filename);
    return -1;
  }

  // Initial counter reset, already to 0 if program just created. If we use
  // another program we reset it to 0
  p->n = 0;
  // Using getline or we pass a size_t argument with the maximum capacity, or we
  // can pass an allocated memory and we pass a size_t pointer cointaining the
  // size in bytes of the just allocated line
  // getline allocates the line by itself
  while ((line_len = getline(&line, &n, p->file)) >= 0) {
    // Remove trailing newline \n replacing it with a string terminator \0
    if (line[line_len - 1] == '\n') {
      line[line_len -1] = '\0';
    }
    // The last line of the file could not end with \n (?) REVIEW 
    if (!(b = block_new(line, p->last, m))) {
      eprintf("Error creating a block from line %s\n", line);
      return -1;
    }
    if (!block_parse(b)) {
      eprintf("Error parsing a block %s\n", line);
      return -1;
    }
    
    if (p->first == NULL) {
      p->first = b;
    } 
    p->last = b;
    p->n++;
  }
  fclose(p->file);
  free(line);
  program_reset(p);
  return 0;
}

block_t *program_next(program_t *p) {
  assert(p);
  if (p->current == NULL) {
    p->current = p->first;
  } else {
    p->current = block_next(p->current);
  }
  return p->current;
}

void program_reset(program_t *p) {
  assert(p);
  p->current = NULL;
}

#ifdef PROGRAM_MAIN

int main(int argc, char const *argv[]) {
  machine_t *m = NULL;
  program_t *p = NULL;

  if (argc != 3) {
    eprintf("I need exactly two arguments: g-code filename and INI filename\n");
    exit(EXIT_FAILURE);
  }  

  m = machine_new(argv[2]);
  if (!m) {
    eprintf("Error in INI file\n");
    exit(EXIT_FAILURE);
  }

  p = program_new(argv[1]);
  if (!p) {
    eprintf("Could not create program\n");
    exit(EXIT_FAILURE);
  }

  program_parse(p, m);

  program_print(p, stdout);


  return 0;
}

#endif