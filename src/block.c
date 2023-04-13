//   ____  _            _
//  | __ )| | ___   ___| | __
//  |  _ \| |/ _ \ / __| |/ /
//  | |_) | | (_) | (__|   <
//  |____/|_|\___/ \___|_|\_\ 
//

#include "block.h"
#include "defines.h"
#include "machine.h"
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <sys/param.h>

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
  machine_t const *machine; // machine object (holding config data)
  struct block *prev;       // to link to previous block in a linked list
  struct block *next;       // to link to next block in a linked list
} block_t;

// STATIC FUNCTIONS
static point_t *start_point(block_t *b);
static int block_set_fields(block_t *b, char cmd, char *argv);
static void block_compute(block_t *b);
static int block_arc(block_t *b);

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// LIFECYCLE
block_t *block_new(char const *line, block_t *prev, machine_t const *machine) {
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

  // Machine parameters
  b->machine = machine;
  b->acc = machine_A(b->machine);

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
  char *start = NULL, *end = NULL;
  point_t *p0 =
      start_point(b); // not a method, not intended to be used outside
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
// We have a G-Code line line "N10 G01 X0 Y100 z210.5 F1000 S5000"
int block_parse(block_t *b) {
  assert(b);
  point_t *p0 = NULL;

  // Variables that counts errors
  int rv = 0;

  // char *strsep(char **stringp, const char *delim)
  /*If  *stringp is NULL, the strsep() function returns NULL and does nothing
     else.  Otherwise, this function finds the first token in the string
     *stringp, that is delimited by one of the bytes in the string delim.  This
     token is terminated by overwriting the delimiter with a null byte ('\0'),
     and *stringp is updated to point past the token.  In case no delimiter was
     found, the token is taken to be the  entire  string  *stringp,  and
     *stringp is made NULL.
  */
  // stringp->A   B   C   _   D   E   _   F
  // It find the first delimiter and substitute it with \0
  // out->A   B   C   \0   stringp->D   E   _   F
  // At next call of the same function
  // A   B   C   \0   out->D   E   \0   stringp->F
  // When stringp finds \0 out is NULL.
  // We need 3 pointers: 1 for the out string, 1 for the stringp and 1 to be a
  // placeholder for the freeing of memory

  // this chunk of code was copied, check rec for tofree meaning of existanceG
  char *word, *line, *tofree;

  tofree = line = strdup(b->line);

  if (!line) {
    eprintf("Could not allocate memory for line string\n");
    return -1; // usually returning 0 means everything is fine
  }

  // tokenization
  while ((word = strsep(&line, " ")) != NULL) {
    rv += block_set_fields(b, toupper(word[0]), word + 1);
    // if it finds error they're added to rv, if not rv is added to 0
    // A word is of type G01 -> word[0] is the letter of the command, word+1 is
    // the first character of the following word body
    // toupper() converts the character to the corresponding upper case, it's
    // include in ctype.h
  }
  free(tofree);

  // Inherit coordinates from previous point
  p0 = start_point(b);
  point_modal(p0, b->target);
  point_delta(p0, b->target, b->delta);
  b->length = point_dist(p0, b->target);

  // Deal with motion blocks
  switch (b->type) {
  case LINE:
    b->acc = machine_A(b->machine);
    b->arc_feedrate = b->feedrate;
    block_compute(b);
    // Should be done already but just to be clear, feedrate too
    break;

  case ARC_CW:
  case ARC_CCW:
    // We need to calculate the arc coordinates, if we get unconsistent center
    // and initial and final point we get an error, the function must return an
    // integer to be added to the variable rv to say we get an error
    if (block_arc(b)) {
      wprintf("Could not calculate arc coordinates\n");
      rv++;
      break;
    }
    b->acc = machine_A(b->machine) / 2.0;

    // To compute minimum there's a function or a macro included in sys/param.h
    b->arc_feedrate = MIN(
        b->feedrate,
        pow(3.0 / 4.0 * pow(machine_A(b->machine), 2) * pow(b->r, 2), 0.25) *
            60);
    // !! 3/4 is a division between 2 integers, in C 3/4=0 !!
    // Feedrate is given in mm per minute so we have to multiply by 60

    block_compute(b);
    break;
  default:
    // If we don't put the default we get a warning we're not handling the
    // remaning cases
    break;
  }

  return rv;
}

// int so it returns a flag on the success of the operation
data_t block_lambda(block_t *b, data_t t, data_t *v) {
  // Lambda is the integral of the ... profile
  assert(b);
  data_t r; // curvilinear ab
  data_t dt_1 = b->prof->dt_1;
  data_t dt_2 = b->prof->dt_2;
  data_t dt_m = b->prof->dt_m;
  data_t a = b->prof->a;
  data_t d = b->prof->d;
  data_t f = b->prof->f;

  if (t < 0) { // before acceleration
    r = 0.0;
    *v = 0.0;
  } else if (t < dt_1) { // during acceleration
    r = a * pow(t, 2) / 2.0;
    *v = a * t;
  } else if (t < dt_1 + dt_m) { // during maintainance
    r = f * (dt_1 / 2.0 + (t - dt_1));
    *v = f;
  } else if (t < dt_1 + dt_m + dt_2) { // during deceleration
    data_t t_2 = dt_1 + dt_m;          // support variable for easier notation
    r = f * dt_1 / 2.0 + f * (dt_m + t - t_2) +
        d / 2.0 * (pow(t, 2) + pow(t_2, 2)) - d * t * t_2;
    *v = f + d * (t - t_2);
  } else { // end of the block
    r = b->prof->l;
    *v = 0;
  }

  r /= b->prof->l;

  // feedrate in mm per minutes
  *v *= 60;

  return r;
}

// We return the value passed as output parameter, a pointer
point_t *block_interpolate(block_t *b, data_t lambda) {
  assert(b);
  // not ideal to allocate and de-allocate everytime we call this function, we
  // use the machine set-point
  point_t *result = machine_setpoint(b->machine);
  // Doing so we just change an already allocated point, that will be allocated
  // only once
  point_t *p0 = start_point(b);
  // just a reference to an already created point that doesn't need to be freed,
  // the variable p0 dies in the function scope

  // Equations of the type:
  // x(t) = x(0) + d_x * lambda
  if (b->type == LINE) {
    point_set_x(result, point_get_x(p0) + point_get_x(b->delta) * lambda);
    point_set_y(result, point_get_y(p0) + point_get_y(b->delta) * lambda);
  } else if (b->type == ARC_CW || b->type == ARC_CCW) {
    point_set_x(result, point_get_x(b->center) +
                            b->r * cos(b->theta0 + b->dtheta * lambda));
    point_set_y(result, point_get_y(b->center) +
                            b->r * sin(b->theta0 + b->dtheta * lambda));
  } else {
    // We're calling block interpolate in a block that shouldn't require to be
    // interpolated
    wprintf("Unexpected block type\n");
    return NULL;
  }
  // z is common to both line and arcs, in arcs z is like the spiral component
  point_set_z(result, point_get_z(p0) + point_get_z(b->delta) * lambda);

  return NULL;
}

//   ____  _        _   _         __                  _   _
//  / ___|| |_ __ _| |_(_) ___   / _|_   _ _ __   ___| |_(_) ___  _ __  ___
//  \___ \| __/ _` | __| |/ __| | |_| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//   ___) | || (_| | |_| | (__  |  _| |_| | | | | (__| |_| | (_) | | | \__ \
//  |____/ \__\__,_|\__|_|\___| |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

static point_t *start_point(block_t *b) {
  assert(b);
  // We return the previous point target, if there is no previous block we give
  // the origin of the machine
  return b->prev ? b->prev->target : machine_zero(b->machine);
}

static int block_set_fields(block_t *b, char cmd, char *arg) {
  assert(b && arg);

  // remember '' for single characters and "" for strings
  switch (cmd) {
  case 'N':
    // We need to convert a string to a numerical value, atol (string to long)
    b->n = atol(arg);
    break;

  case 'G':
    b->type = (block_type_t)atoi(arg);
    // This requires the cast to block_type_t struct
    break;

  case 'X':
    point_set_x(b->target, atof(arg));
    break;

  case 'Y':
    point_set_y(b->target, atof(arg));
    break;

  case 'Z':
    point_set_z(b->target, atof(arg));
    break;

  case 'I':
    b->i = atof(arg);
    break;

  case 'J':
    b->j = atof(arg);
    break;

  case 'R':
    b->r = atof(arg);
    break;

  case 'F':
    b->feedrate = atof(arg);
    break;

  case 'S':
    b->spindle = atof(arg);
    break;

  case 'T':
    // Tool is a size_t type, a long integer so atol() is required, Spindle and
    // feedrate are data_t type that we defined as double so we use atof(),
    // (float)
    b->tool = atol(arg);
    break;

  default:
    wprintf("Unsopperted command received %c\n", cmd);
    return 1;
    break;
  }

  // Another possible error is whenever we have both R and IJ specified, they're
  // redundant
  if (b->r && (b->i || b->j)) {
    wprintf("Cannot mix R and I,J\n");
    return 1;
  }

  return 0;
}

// Dq is the rounding time added, tq is quantization time
static data_t quantize(data_t t, data_t tq, data_t *dq) {
  data_t q;
  q = ((size_t)(t / tq) + 1) * tq;
  *dq = q - t;
  // time to be added to t in order to reach q
  // doing so we return q and dq since we passed it's pointer
  return q;
}

// Valid for both line and arcs
static void block_compute(block_t *b) {
  assert(b);
  data_t A, a, d;                  // Max acc, actual a, deceleration
  data_t dt, dt_1, dt_2, dt_m, dq; // total duration, acc duration, dec
                                   // duration, maintainance duration and ...
  data_t f_m, l;                   // arc feedrate and length

  A = b->acc;
  f_m = b->arc_feedrate / 60.0;
  l = b->length;
  dt_1 = f_m / A;
  dt_2 = dt_1;
  dt_m = l / f_m - (dt_1 + dt_2) / 2.0; // non ho capito perchè diviso per 2

  if (dt_m > 0) { // Trapezoidal profile
    // Total duration is the next integer after total duration rounded to next
    // multiple of quantization time
    dt = quantize(dt_1 + dt_m + dt_2, machine_tq(b->machine), &dq);
    dt_m += dq;
    f_m = (2 * l) / (dt_1 + dt_2 + 2 * dt_m);
  } else { // Triangular profile (short block)
    dt_1 = dt_2 = sqrt(l / A);
    dt = quantize(dt_1 + dt_2, machine_tq(b->machine), &dq);
    dt_m = 0;
    dt_2 += dq;
    f_m = 2 * l / (dt_1 + dt_2);
  }
  a = f_m / dt_1;
  d = -(f_m / dt_2);

  b->prof->dt_1 = dt_1;
  b->prof->dt_2 = dt_2;
  b->prof->dt_m = dt_m;
  b->prof->dt = dt;
  b->prof->a = a;
  b->prof->d = d;
  b->prof->f = f_m;
  b->prof->l = l;
}

static int block_arc(block_t *b) { return 0; }

//   _____         _                     _
//  |_   _|__  ___| |_   _ __ ___   __ _(_)_ __
//    | |/ _ \/ __| __| | '_ ` _ \ / _` | | '_ \ 
//    | |  __/\__ \ |_  | | | | | | (_| | | | | |
//    |_|\___||___/\__| |_| |_| |_|\__,_|_|_| |_|

#ifdef BLOCK_MAIN

int main(int argc, char const *argv[]) {
  machine_t *m = machine_new(argv[1]);
  block_t *b1 = NULL, *b2 = NULL, *b3 = NULL, *b4 = NULL;

  if (!m) {
    eprintf("Error creating machine\n");
    exit(EXIT_FAILURE);
  }

  b1 = block_new("N10 G01 X90 Y90 Z100 T3 F1000", NULL, m);
  block_parse(b1);
  b2 = block_new("N20 G01 y100 s2000", b1, m);
  block_parse(b2);
  b3 = block_new("N30 G01 Y200", b2, m);
  block_parse(b3);
  b4 = block_new("N40 G01 x0 y0 z0", b3, m);
  block_parse(b4);

  block_print(b1, stderr);
  block_print(b2, stderr);
  block_print(b3, stderr);
  block_print(b4, stderr);

  wprintf("Interpolation of block 20 (duration: %f)\n", block_dt(b2));
  {
    data_t t = 0, tq = machine_tq(m), dt = block_dt(b2);
    data_t lambda, v = 0;
    point_t *pos = NULL;
    printf("t lambda v x y z\n");
    // svg format
    for (t = 0; /* Exercise: time should start at 0 and exactly stop at dt */;
         t += tq) {
      // Exercise
    }
  }

  block_free(b1);
  block_free(b2);
  block_free(b3);
  block_free(b4);

  return 0;
}

#endif