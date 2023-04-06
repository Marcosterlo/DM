//   ____  _            _
//  | __ )| | ___   ___| | __
//  |  _ \| |/ _ \ / __| |/ /
//  | |_) | | (_) | (__|   <
//  |____/|_|\___/ \___|_|\_\                          

#include "block.h"

//   ____            _                 _   _
//  |  _ \  ___  ___| | __ _ _ __ __ _| |_(_) ___  _ __  ___
//  | | | |/ _ \/ __| |/ _` | '__/ _` | __| |/ _ \| '_ \/ __|
//  | |_| |  __/ (__| | (_| | | | (_| | |_| | (_) | | | \__ \
//  |____/ \___|\___|_|\__,_|_|  \__,_|\__|_|\___/|_| |_|___/

typedef struct {
  data_t a, d;             // acceleration and deceleration
  data_t f, l;             // nominal feedrate and length
  data_t fs, fe;           // initial and final feedrate
  data_t dt_1, dt_m, dt_2; // trapezoidal profile times
  data_t dt;               // total duration
} block_profile_t;

typedef struct block {
  char *s line; // G-Code string
  block_type_t type;
  size_t n;        // Block number
  size_t tool;     // Tool number
  data_t feedrate; // feedrate in mm/min
  // Remember feedrate in arcs could be lower due to accelaration limit and
  // centiripetal acceleration
  data_t arc_feedrate; // actual nominal feedrate along an arc motion
  data_t spindle;      // spindle rotational speed in RPM
  point_t *target;     // Final coordinates of the block
  point_t *delta;      // Projections
  point_t *center;     // Coordinate of the center of the arc
  data_t length;       // of the segment or arc
  // If it is an arc the G-Code passes I,J and a radius
  data_t i, j, r;        // arc parameters
  data_t theta0, dtheta; // inizial angle and velocity
  struct block *prev;    // to link to previous block in a linked list
  struct block *next;    // to link to next block in a linked list
} block_t;
