//   ____       _       _
//  |  _ \ ___ (_)_ __ | |_
//  | |_) / _ \| | '_ \| __|
//  |  __/ (_) | | | | | |_
//  |_|   \___/|_|_| |_|\__|

#include "point.h"
#include <string.h>
#include <math.h>

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Setters
void point_set_x(point_t *p, data_t x) {
  assert(p);
  p->x = x;
  // Bitwise boolean operations to set the right s bit
  // xxxx xxxx -> initial value of s
  // 0000 0001 -> X_SET
  // ------------------
  // xxxx xxx1 -> The result must only change this bit leaving the rest unchanged. This is a bitwise OR
  // Recall || and && are logical or and and, | adn & are bitwise or and and
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
    exit(EXIT_FAILURE); //?
  }

  // Usually a good idea is to initialize newly allocated memory, Linux
  // shouldn't set memory to 0 by defualt
  memset(p, 0, sizeof(p));
  // see man memset for info, sets the passed memory to a constant byte, second
  // argument, for the lenth l third argument

  return p;
}

// Free memory
void point_free(point_t *p) {

  assert(p); // gives info in debugging fase in case it breaks

  free(p);
}

// Distance between 2 points
data_t point_dist(point_t const *from, point_t const *to) {
  
  assert(from && to);

  return sqrt(
    pow(to->x - from->x, 2) + 
    pow(to->y - from->y, 2) + 
    pow(to->z - from->z, 2)
  ); 
}

// Point delta, calculating the delta projections into the delta point_t pointer
void point_delta(point_t const *from, point_t const *to, point_t *delta) {

  assert(from && to);

  delta->x = to->x - from->x;
  delta->y = to->y - from->y;
  delta->z = to->z - from->z;
}

// Import form previous coordinate all the values that have not been changed
// second point passed is no more const because we are changing/creating a new
// one
void point_modal(point_t const *from, point_t *to) {

  assert(from);

}