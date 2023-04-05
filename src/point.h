//   ____       _       _
//  |  _ \ ___ (_)_ __ | |_
//  | |_) / _ \| | '_ \| __|
//  |  __/ (_) | | | | | |_
//  |_|   \___/|_|_| |_|\__|
//
// Point class

// since header file we add a double include guard
#ifndef POINT_H
#define POINT_H

#include "defines.h"

typedef struct {
  data_t x, y, z;
  uint8_t s;
} point_t;

// The s bit in this sense has to be interpreted bitwise, we have to understand if x,y,z are valid or undefined, we just need a bit per coordinate so we'll use a total of 3 bit out of the 8 of the byte:
// x set -> 00000001 = 1
// y set -> 00000010 = 2
// z set -> 00000100 = 4
// xyz set -> 00000111 = 7
// We create a bit mask

#define X_SET '\1'
#define Y_SET '\2'
#define Z_SET '\4'
#define XYZ_SET '\7'

//   _____                 _   _                 
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___ 
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Create a new point
point_t *point_new();

// Free memory
void point_free(point_t *p);

// Distance between 2 points
data_t point_dist(point_t const *from, point_t const *to);
                                              
// Point delta, calculating the delta projections into the delta point_t pointer
void point_delta(point_t const *from, point_t const *to, point_t *delta);

// Import form previous coordinate all the values that have not been changed
// second point passed is no more const because we are changing/creating a new one
void point_modal(point_t const *from, point_t *to);

#endif