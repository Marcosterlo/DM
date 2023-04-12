//   ____  _            _
//  | __ )| | ___   ___| | __
//  |  _ \| |/ _ \ / __| |/ /
//  | |_) | | (_) | (__|   <
//  |____/|_|\___/ \___|_|\_\ 
//

#include "block.h"
#include "defines.h"

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
  char *line; // G-Code string
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
  data_t acc;            // actual acceleration
  block_profile_t *prof;
  struct block *prev; // to link to previous block in a linked list
  struct block *next; // to link to next block in a linked list
} block_t;

// STATIC FUNCTIONS
static point_t *point_zero(block_t *b);

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// LIFECYCLE
block_t *block_new(char const *line, block_t *prev) {
  assert(line);
  block_t *b = malloc(sizeof(block_t));
  if (!b) {
    eprintf("Could not allocate memory for a block\n");
    goto fail;
  }

  if (prev) { // Copy memory from previous block
    memcpy(b, prev, sizeof(block_t));
    b->prev = prev;
    prev->next = b;
  } else {
    memset(b, 0, sizeof(block_t));
  }

  // Arc parameters need to be explicitely set to 0 every time, all non modal
  // parameters
  b->i = b->j = b->r = 0;

  // Fields to be calculated
  b->length = 0;
  b->prof = malloc(sizeof(block_profile_t));
  if (!b->prof) {
    eprintf("Could not allocate memory for block profile\n");
    goto fail;
  }
  b->line = strdup(line);
  if (!(b->line)) {
    eprintf("Could not allocate memory for block line\n");
    goto fail;
  }
  b->target = point_new();
  b->delta = point_new();
  b->center = point_new();
  if (!b->center || !b->delta || !b->target) {
    eprintf("Could not allocate points in block\n");
    goto fail;
  }
  b->type = NO_MOTION; // by default, will be changed by parse function
  b->acc = 0; // To be substituted with nominal value of the machine, for the
              // moment we leave 0

  return b;

// Only good way to use jumps and label, usually it's best to avoid using them.
// Use goto only when strictly necessary. The only good use is to control the
// exit point of a function, never use it instead of conditions and loops
fail:
  if (b)
    block_free(b);
  return NULL;
}
void block_free(block_t *b) {
  assert(b);
  if (b->line)
    free(b->line);
  if (b->prof)
    free(b->prof);
  if (b->target)
    point_free(b->target);
  if (b->delta)
    point_free(b->delta);
  if (b->center)
    point_free(b->center);
  free(b);
}

void block_print(block_t *b, FILE *out) {
  assert(b && out);
  char *start, *end;
  point_t *p0 = point_zero(b); // not a method, not intended to be used outside
                               // so not in the header, we define the function
                               // as static, only visible inside and not outside
  point_inspect(p0, &start);
  point_inspect(b->target, &end);
  fprintf(out, "%03lu, %s->%s F%7.1f S%7.1f T%2lu (G%02d)\n", b->n, start, end,
          b->feedrate, b->spindle, b->tool, b->type);
  free(start);
  free(end);
}

// ACCESSORS (only the public ones we want the user to have access to)
// All getters -> all consante

#define block_getter(typ, par, name)                                           \
  typ block_##name(block_t const *b) {                                         \
    assert(b);                                                                 \
    return b->par;                                                             \
  }

block_getter(data_t, length, length);
block_getter(data_t, dtheta, dtheta);
block_getter(data_t, prof->dt, dt);
block_getter(data_t, r, r);
block_getter(size_t, n, n);
block_getter(block_type_t, type, type);
block_getter(char *, line, line);
block_getter(point_t *, center, center);
block_getter(point_t *, target, target);
block_getter(block_t *, next, next);

// METHODS
// G-Code line string parsing
int block_parse(block_t *b) { 

  return 0; 
}

// int so it returns a flag on the success of the operation
data_t block_lambda(block_t *b, data_t time, data_t *v) { 

  return 0;
}

// We return the value passed as output parameter, a pointer
point_t *block_interpolate(block_t *b, data_t lambda) { 

  return NULL; 
}

//   ____  _        _   _         __                  _   _
//  / ___|| |_ __ _| |_(_) ___   / _|_   _ _ __   ___| |_(_) ___  _ __  ___
//  \___ \| __/ _` | __| |/ __| | |_| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//   ___) | || (_| | |_| | (__  |  _| |_| | | | | (__| |_| | (_) | | | \__ \
//  |____/ \__\__,_|\__|_|\___| |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

static point_t *point_zero(block_t *b) {
  point_t *p = point_new();
  return p;
}