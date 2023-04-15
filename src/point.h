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

//   ____            _                 _   _
//  |  _ \  ___  ___| | __ _ _ __ __ _| |_(_) ___  _ __  ___
//  | | | |/ _ \/ __| |/ _` | '__/ _` | __| |/ _ \| '_ \/ __|
//  | |_| |  __/ (__| | (_| | | | (_| | |_| | (_) | | | \__ \
//  |____/ \___|\___|_|\__,_|_|  \__,_|\__|_|\___/|_| |_|___/

// Point object struct
// typedef struct {
//   data_t x, y, z; // coordinates
//   uint8_t s;      // bitmask
// } point_t;

// I do not want to expose inner args of the object to everyone, sometimes there
// are fields that are not supposed to be changed by the user or that must not
// be changed unless invoked by some method. Later on we will possibly change
// the name of a variable, if we do it all the code using this library might
// break. It's preferable to move this declaration from header to source code.
// We just say there is a structure named point_t
// The bitmask is masked to the user of this library, it is only used in the .c
// file, so not by everyone

// Point object struct (Opaque object!)
typedef struct point point_t;

// The s bit in this sense has to be interpreted bitwise, we have to understand
// if x,y,z are valid or undefined, we just need a bit per coordinate so we'll
// use a total of 3 bit out of the 8 of the byte: x set -> 00000001 = 1 y set ->
// 00000010 = 2 z set -> 00000100 = 4 xyz set -> 00000111 = 7 We create a bit
// mask

#define X_SET '\1'
#define Y_SET '\2'
#define Z_SET '\4'
#define XYZ_SET '\7'

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// LIFECYCLE (instance creation/destruction)
point_t *point_new();
void point_free(point_t *p);

// ACCESSORS (getting/setting object fields)
// setters
void point_set_x(point_t *p, data_t x);
void point_set_y(point_t *p, data_t y);
void point_set_z(point_t *p, data_t z);
void point_set_xyz(point_t *p, data_t x, data_t y, data_t z);
// getters
data_t point_x(point_t const *p);
data_t point_y(point_t const *p);
data_t point_z(point_t const *p);

// METHODS (Functuions that operate on an object)
data_t point_dist(point_t const *from, point_t const *to);
void point_delta(point_t const *from, point_t const *to, point_t *delta);
void point_modal(point_t const *from, point_t *to);
void point_inspect(point_t const *p, char **desc);

#endif // POINT_H