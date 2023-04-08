//   ____  _            _
//  | __ )| | ___   ___| | __
//  |  _ \| |/ _ \ / __| |/ /
//  | |_) | | (_) | (__|   <
//  |____/|_|\___/ \___|_|\_\
//
// G-Code block class

#ifndef BLOCK_H
#define BLOCK_H

#include "defines.h"
#include "point.h"
#include <string.h>

//   _____
//  |_   _|   _ _ __   ___  ___
//    | || | | | '_ \ / _ \/ __|
//    | || |_| | |_) |  __/\__ \
//    |_| \__, | .__/ \___||___/
//        |___/|_|

// Opaque struct representing the G-Code block
typedef struct block block_t;

// Block types
// Different types of motion in G-Code: G00 -> rapid, G01 -> linear
// interpolation and so on, since we're on Linux RAPID is by default 0, better
// to specify
typedef enum { RAPID = 0, LINE, ARC_CW, ARC_CCW, NO_MOTION } block_type_t;

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// LIFECYCLE
block_t *block_new(char const *line, block_t *prev);
// new block starting from single line G-Code, and the pointer to the previous
// element in the list
void block_free(block_t *b);
void block_print(block_t *b, FILE *out);
// print description into a stream, file of stderr for exampleDM/src/block.h

// ACCESSORS (only the public ones we want the user to have access to)
// All getters -> all consant
data_t block_length(block_t const *b);
data_t block_dtheta(block_t const *b);
data_t block_dt(block_t const *b);
data_t block_r(block_t const *b);
block_type_t block_type(block_t const *b);
char *block_line(block_t const *b);
size_t block_n(block_t const *b);
point_t *block_center(block_t const *b);
point_t *block_target(block_t const *b);
block_t *block_next(block_t const *b);


// METHODS
// G-Code line string parsing
int block_parse(block_t *b); 
// int so it returns a flag on the success of the operation
data_t block_lambda(block_t *b, data_t time, data_t *v);
// We return the value passed as output parameter, a pointer
point_t *block_interpolate(block_t *b, data_t lambda);



#endif // BLOCK_H