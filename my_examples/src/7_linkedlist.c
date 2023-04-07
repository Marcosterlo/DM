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
  char *id; // Name/Index of my element
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
  strncpy(e->id, id, strlen(id));
  // Little bit different from strcpy, strcpy doesn't require syze of source,
  // strncpy doesn't always add the string terminator if the string is already
  // full?
  return e;
}

// Free the element
void element_free(element_t *e) {
  // We have to free every heap allocated element stored inside the struct
  // element
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
list_t *list_new(char *id) {
  list_t *l = malloc(sizeof(list_t));
  // Create first element
  element_t *e = element_new(id);
  // List initialization
  l->first = e;
  l->last = e;
  l->length = 1;
  return l;
}

// Append element at the end of my list
void list_append_element(list_t *list, element_t *e) {
  // Link the two elements
  list->last->next = e;
  e->prev = list->last; // Old last value
  list->last = e;       // New last value
  // Next of e set to null
  e->next = NULL;
  list->length++; // list length update
}

// Append a new element
element_t *list_append_(list_t *list, char *id) {
  element_t *e = element_new(id);
  list_append_element(list, e);
  return e;
}

// inserting an existing element after a given ID
//
//                             "after"
//         ┌───┬──────┐     ┌───┬──────┐       ┌───┬──────┐
// NULL ◄──┤PRV│      │◄────┤ P │      │     ┌─┤ P │      │
//         ├───┘  ┌───┤     ├───┘  ┌───┤     │ ├───┘  ┌───┤
//         │      │NXT├────►│      │ N ├──┐  │ │      │ N ├──► NULL
//         └──────┴───┘     └────▲─┴───┘  │  │ └───▲──┴───┘
//                               │   ┌───┐▼──▼──┐  │
//                               └───┤ P │      │  │
//                       new element ├───┘  ┌───┤  │
//                    to be inserted │      │ N ├──┘
//                                   └──────┴───┘
//

// Insert a new element after a certain ID
void list_insert_element(list_t *list, element_t *new, char *after) {
  element_t *e; // Temporary element
  e = list->first;
  // Iteration until the correct ID
  do {
    if (strcmp(e->id, after) == 0) {
      new->next = e->next;
      new->prev = e;
      e->next->prev = new;
      e->next = new;
      break;
    }
  } while ((e = e->next));
}

// Add new element to my list
element_t *list_insert(list_t *list, char *id, char *after) {
  element_t *e = element_new(id);
  list_insert_element(list, e, after);
  return e;
}

// Delete one element from the list
void list_delete_element(list_t *list, char *id) {
  element_t *e; // Temporary element
  e = list->first;
  do {
    if (strcmp(e->id, id) == 0) {
      e->prev->next = e->next;
      e->next->prev = e->prev;
      element_free(e);
      list->length--;
      break;
    }
  } while ((e = e->next));
}

// Free the list
void list_free(list_t *list) {
  element_t *e, *next; // Temporary element
  e = list->first;
  do {
    next = e->next;
    list_delete_element(list, e->id);
  } while ((e = next));
  free(list);
}

//   _
//  | |    ___   ___  _ __
//  | |   / _ \ / _ \| '_ \ 
//  | |__| (_) | (_) | |_) |
//  |_____\___/ \___/| .__/
//                   |_|

typedef enum { ASCENDING = 0, DESCENDING, NUM_OF_LOOP_ORDERS } loop_order_t;

// Function prototypes
typedef void (*loop_fun_t)(element_t *e, loop_order_t o, void *userdata);
//       (a) |----(b)----| |--------------------(c)--------------------|
// a = the prototype return type
// b = prototype type function
// c = prototype function arguments

// Doing so we create a prototype of a function that can be used for callbacks:
// when we pass a function as an argument to another function when for example
// we have to implement a similire task with little difference we could
// differentiate trough this kind of functions

// General function that depending on which loop_fun_t we pass will do different
// things
// Loop inside the list and execute fun on each element
void list_loop(list_t *list, loop_fun_t fun, loop_order_t order,
               void *userdata) {
  element_t *e; // Tmp element

  // First element according to order
  if (order == ASCENDING)
    e = list->first;
  else
    e = list->last;

  // Loop
  do {
    // Execute fun on element e
    fun(e, order, userdata);

    // New value
    if (order == ASCENDING)
      e = e->next;
    else
      e = e->prev;

  } while (e);
}

// Function implementation based on prototype
void print_element(element_t *e, loop_order_t o, void *userdata) {
  printf("%10s: %15p -> %15p\n", e->id, e->prev, e->next);
}

void print_element_with_index(element_t *e, loop_order_t o, void *userdata) {
  // Explicit cast of userdata into size_t pointer, this is the iterator
  size_t *i = (size_t *)userdata;
  printf("list[%lu]: %s\n", (*i), e->id);
  if (o == ASCENDING)
    (*i)++;
  else
    (*i)--;
}

int main() {
  char ids[4][10] = {"one", "two", "three", "four"};
  element_t *e;
  size_t i;
  list_t *list = list_new("zero");
  for (i = 0; i < 4; i++) {
    e = element_new(ids[i]);
    printf("Element %s is added!\n", ids[i]);
    list_append_element(list, e);
  }

  // Loop ascending
  i = 0;
  list_loop(list, print_element_with_index, ASCENDING, &i);

  // Loop descending
  printf("Descending order\n");
  i = list->length - 1;
  list_loop(list, print_element_with_index, DESCENDING, &i);

  // Print element informations
  printf("Element info\n");
  list_loop(list, print_element, ASCENDING, NULL);

  // Remove one element
  printf("Remove the two element\n");
  list_delete_element(list, "two");

  i = 0;
  list_loop(list, print_element_with_index, ASCENDING, &i);

  // Free the list
  list_free(list);
  // printf("List length: %lu\n", list->length); This will give segmentation
  // fault error because the pointer list is freed

  return 0;
}
