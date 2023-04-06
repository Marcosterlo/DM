// 2 types of list: element pointing only to the next one and bi-directional
// ones

//   _     _       _            _   _ _     _
//  | |   (_)_ __ | | _____  __| | | (_)___| |_
//  | |   | | '_ \| |/ / _ \/ _` | | | / __| __|
//  | |___| | | | |   <  __/ (_| | | | \__ \ |_
//  |_____|_|_| |_|_|\_\___|\__,_| |_|_|___/\__|

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//         ┌───┬──────┐     ┌───┬──────┐     ┌───┬──────┐
// NULL ◄──┤PRV│      │◄────┤ P │      │◄────┤ P │      │
//         ├───┘  ┌───┤     ├───┘  ┌───┤     ├───┘  ┌───┤
//         │      │NXT├────►│      │ N ├────►│      │ N ├──► NULL
//         └──────┴───┘     └──────┴───┘     └──────┴───┘

typedef struct element {
  char *id // Name/Index of my element
      struct element *prev;
  struct element *next;
  // USER DATA
  // point_t point; and so on
} element_t;

// Create a new element
element_t *element_new(char *id) {

  element_t *e = malloc(sizeof(element_t));

  // Set/Initialize the element members
  memset(e, 0, sizeof(element_t)); // see man memset for further info

  // Id assignment
  e->id = malloc(strlen(id) + 1); // to reserve space to \0
  strncpy(e->id, id, sizeof(id));
  // Little bit different from strcpy, strcpy doesn't require syze of source,
  // strncpy doesn't always add the string terminator if the string is already
  // full?
  return e;
}

// Free the element
void element_free(element_t *e) {
  // We have to free every heap allocated element stored inside the struct element
  free(e->id);
  free(e);
}

//   _     _     _   
//  | |   (_)___| |_ 
//  | |   | / __| __|
//  | |___| \__ \ |_ 
//  |_____|_|___/\__|
                  
typedef struct {
  element_t *first, *last;
  size_t length;
} list_t;

// New list