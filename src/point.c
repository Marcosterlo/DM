//   ____       _       _
//  |  _ \ ___ (_)_ __ | |_
//  | |_) / _ \| | '_ \| __|
//  |  __/ (_) | | | | | |_
//  |_|   \___/|_|_| |_|\__|

#include "point.h"
#include <math.h>
#include <string.h>

// Point object struct
typedef struct point {
  data_t x, y, z; // coordinates
  uint8_t s;      // bitmask
} point_t;

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Setters
// This kind of variables can be directly defined by compiler in a cmake
// configuration files, this make the code flexible and eventually portable
// between different platforms if we differentiate the code in a way like this
#ifdef NOT_DRY
void point_set_x(point_t *p, data_t x) {
  assert(p);
  p->x = x;
  // Bitwise boolean operations to set the right s bit
  // xxxx xxxx -> initial value of s
  // 0000 0001 -> X_SET
  // ------------------
  // xxxx xxx1 -> The result must only change this bit leaving the rest
  // unchanged. This is a bitwise OR Recall || and && are logical or and and, |
  // adn & are bitwise or and and
  p->s |= X_SET;
}
void point_set_y(point_t *p, data_t y) {
  assert(p);
  p->y = y;
  p->s |= Y_SET;
}
void point_set_z(point_t *p, data_t z) {
  assert(p);
  p->z = z;
  p->s |= Z_SET;
}
// Getters
data_t point_x(point_t const *p) {
  assert(p);
  return p->x;
}
data_t point_y(point_t const *p) {
  assert(p);
  return p->y;
}
data_t point_z(point_t const *p) {
  assert(p);
  return p->z;
}
#else
// D.R.Y. version: pre-processor macros
// backslash to go newline in macro definition
#define point_accessor(axis, bitmask)                                          \
  void point_set_##axis(point_t *p, data_t value) {                            \
    assert(p);                                                                 \
    p->axis = value;                                                           \
    p->s |= bitmask;                                                           \
  }                                                                            \
  data_t point_get_##axis(point_t const *p) {                                  \
    assert(p);                                                                 \
    return p->axis;                                                            \
  }
point_accessor(x, X_SET);
point_accessor(y, Y_SET);
point_accessor(z, Z_SET);
#endif

// Out of the macro cause it's a function on its own to define xyz at the same
// time and not by invoking singularly the point accessors
void point_set_xyz(point_t *p, data_t x, data_t y, data_t z) {
  assert(p);
  p->x = x;
  p->y = y;
  p->z = z;
  p->s |= XYZ_SET;
}

// Create a new point
point_t *point_new() {

  point_t *p = malloc(sizeof(point_t));
  // Always check if allocation succeded
  if (!p) {
    eprintf("Error allocating memory for a point\n");
    return NULL;
  }
  // Usually a good idea is to initialize newly allocated memory, Linux
  // shouldn't set memory to 0 by defualt
  memset(p, 0, sizeof(*p));
  // see man memset for info, sets the passed memory to a constant byte, second
  // argument, for the lenth l third argument
  return p;
}

// Free memory
void point_free(point_t *p) {
  // Assert is a function that checks a condition, in this case if p is not
  // NULL, If false assert stop and tells us in compiling time where the error
  // is, it's a faster way to debug instead of checking manually and adding a
  // print function to determine what broke
  assert(p); // gives info in debugging fase in case it breaks

  free(p);
}

#define FIELD_SIZE 8 // Desired number of decimal digits
void point_inspect(point_t const *p, char **desc) {
  assert(p);
  // The size depends on how many decimal we want in the number
  char str_x[FIELD_SIZE + 1], str_y[FIELD_SIZE + 1], str_z[FIELD_SIZE + 1];
  // +1 to take into account the string terminator \0
  if (p->s & X_SET) {
    sprintf(str_x, "%*.3f", FIELD_SIZE, p->x);
    // First we pass the string we want to write into, the * is substituted with
    // the first parameter passed after the format, in this case it's like
    // passing %8.3f
  } else {
    sprintf(str_x, "%*s", FIELD_SIZE, "-"); // It's like writing 8 characters -
  }

  if (p->s & Y_SET) {
    sprintf(str_y, "%*.3f", FIELD_SIZE, p->y);
  } else {
    sprintf(str_y, "%*s", FIELD_SIZE, "-"); // It's like writing 8 characters -
  }

  if (p->s & Z_SET) {
    sprintf(str_z, "%*.3f", FIELD_SIZE, p->z);
  } else {
    sprintf(str_z, "%*s", FIELD_SIZE, "-"); // It's like writing 8 characters -
  }

  // Now we combine the 3 string in a single one that will be allocated in the
  // stack and returned as output

  if (asprintf(desc, "[%s %s %s]", str_x, str_y, str_z) == -1) {
    eprintf("Could not allocate memory for point description.\n");
    exit(EXIT_FAILURE);
  }
  // Everytime we allocate a memory we have to check it's success or not,
  // asprintf returns a integer wether the operation was successfull or not, in
  // particular it return -1 if the operation failed
}
#undef FIELD_SIZE // The macro is only existing in this set of lines, it's risky
                  // to have a macro with similar name and different value

// Distance between 2 points
data_t point_dist(point_t const *from, point_t const *to) {

  assert(from && to);

  return sqrt(pow(to->x - from->x, 2) + pow(to->y - from->y, 2) +
              pow(to->z - from->z, 2));
}

// Point delta, calculating the delta projections into the delta point_t pointer
void point_delta(point_t const *from, point_t const *to, point_t *delta) {

  assert(from && to && delta);

  point_set_xyz(delta, to->x - from->x, to->y - from->y, to->z - from->z);
}

// Import form previous coordinate all the values that have not been changed
// second point passed is no more const because we are changing/creating a new
// one
void point_modal(point_t const *from, point_t *to) {

  assert(from && to);

  if (!(to->s & X_SET) && (from->s & X_SET)) {
    point_set_x(to, from->x);
  }

  if (!(to->s & Y_SET) && (from->s & Y_SET)) {
    point_set_y(to, from->y);
  }

  if (!(to->s & Z_SET) && (from->s & Z_SET)) {
    point_set_z(to, from->z);
  }
}

#ifdef POINT_MAIN
int main(int argc, char const *argv[]) {
  point_t *p1, *p2, *p3;
  char *desc;
  // Create 3 points
  p1 = point_new();
  p2 = point_new();
  p3 = point_new();

  // Set p1 to origin
  point_set_xyz(p1, 0, 0, 0);

  // Only set X and Y on second point
  point_set_x(p2, 100);
  point_set_y(p2, 110);
  point_inspect(p2, &desc);
  printf("Initial p2: %s\n", desc);

  // Modal
  point_modal(p1, p2);
  point_inspect(p2, &desc);
  printf("After modal p2: %s\n", desc);

  // Distance
  printf("Distance p1->p2: %f\n", point_dist(p1, p2));

  // Delta
  point_delta(p1, p2, p3);
  point_inspect(p3, &desc);
  printf("Projections p1->p2: %s\n", desc);

  // Free the memory
  point_free(p1);
  point_free(p2);
  point_free(p3);
  free(desc);

  return 0;
}
#endif