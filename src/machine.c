//   __  __            _     _
//  |  \/  | __ _  ___| |__ (_)_ __   ___
//  | |\/| |/ _` |/ __| '_ \| | '_ \ / _ \
//  | |  | | (_| | (__| | | | | | | |  __/
//  |_|  |_|\__,_|\___|_| |_|_|_| |_|\___|

#include "machine.h"
#include "toml.h"
#include <string.h>

typedef struct machine {
  data_t A;  // max acceleration
  data_t tq; // quantization step
  data_t max_error, error;
  point_t *zero;
  point_t *setpoint, *position;
} machine_t;

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Lifecycle

// We crate passing the name of a configuration file containing all machine
// parameters

#define BUFLEN 1024

machine_t *machine_new(char const *cfg_path) {
  machine_t *m = NULL;
  FILE *ini_file = NULL;
  toml_table_t *conf = NULL;
  // String to be used as error buffer for toml library
  char errbuf[BUFLEN];

  m = malloc(sizeof(*m));

  if (!m) {
    eprintf("Could not allocate memory for machine object\n");
    return NULL;
  }

  // Memory initialization to 0, we're writing zeros in a number equal to the
  // byte size of the structurer
  // We also have to include string.h to use memset
  memset(m, 0, sizeof(*m));

  // Default values
  m->A = 100;
  m->max_error = 0.010;
  m->tq = 0.005;
  m->zero = point_new();
  m->setpoint = point_new();
  m->position = point_new();
  point_set_xyz(m->zero, 0, 0, 0);
  // if we don't do that the zero coordinates are undefined for how we
  // programmed the point class, we have to explicitely set to 0 in
  // order to make the bitmask correctly set

  // Import values form a INI file
  ini_file = fopen(cfg_path, "r");

  if (!ini_file) {
    eprintf("Could not open the file %s\n", cfg_path);
    goto fail;
  }

  conf = toml_parse_file(ini_file, errbuf, BUFLEN);
  fclose(ini_file);

  if (!conf) {
    eprintf("Could not parse ini file: %s\n", errbuf);
    goto fail;
  }

  /*
  One way to do it
  toml_datum_t d;
  toml_table_t *ccnc = toml_table_in(conf, "C-CNC");
  d = toml_double_in(ccnc, "A");
  if (!d.ok) {
    m->A = d.u.d; // We're extracting the double value from the union field of
  the toml_datum_t d
  }

  Doing so we should write this code repeatedly for every parameter, it's better
  to define a MACRO
  */

// Macro to read integers
#define T_READ_I(d, machine, tab, key)                                         \
  d = toml_int_in(tab, #key);                                                  \
  if (!d.ok)                                                                   \
    wprintf("Missing %s:%s\n", toml_table_key(tab), #key);                     \
  else                                                                         \
    machine->key = d.u.i;

  // in toml_int_in we passed #key to pass key as a string

#define T_READ_D(d, machine, tab, key)                                         \
  d = toml_double_in(tab, #key);                                               \
  if (!d.ok)                                                                   \
    wprintf("Missing %s:%s\n", toml_table_key(tab), #key);                     \
  else                                                                         \
    machine->key = d.u.d;

#define T_READ_S(d, machine, tab, key)                                         \
  d = toml_string_in(tab, #key);                                               \
  if (!d.ok)                                                                   \
    wprintf("Missing %s:%s\n", toml_table_key(tab), #key);                     \
  else                                                                         \
    strncpy(machine->key, d.u.s, strlen(machine->key));

  // We create a local block to initialize and use the variables necessary for
  // methods creation, variables in the block are only visible in the block
  // scope
  {
    toml_datum_t d;
    toml_table_t *ccnc = toml_table_in(conf, "C-CNC");
    if (!ccnc) {
      wprintf("Missing C-CNC section\n");
      goto fail;
    }

    // MACRO CREATION
    T_READ_D(d, m, ccnc, A);
    T_READ_D(d, m, ccnc, max_error);
    T_READ_D(d, m, ccnc, tq);
  }

  toml_free(conf);
  return m;

fail:
  machine_free(m);
  return NULL;
}

#undef BUFLEN

void machine_free(machine_t *m) {
  assert(m);
  if (m->zero)
    point_free(m->zero);
  if (m->setpoint)
    point_free(m->setpoint);
  if (m->position)
    point_free(m->position);
  free(m);
}

// Accessors

// MACRO definition
#define machine_getter(typ, par)                                               \
  typ machine_##par(machine_t const *m) {                                      \
    assert(m);                                                                 \
    return m->par;                                                             \
  }

// MACRO usage
machine_getter(data_t, A);
machine_getter(data_t, tq);
machine_getter(data_t, max_error);
machine_getter(data_t, error);
machine_getter(point_t *, zero);
machine_getter(point_t *, setpoint);
machine_getter(point_t *, position);

// Methods, public functions to deal with the class
void machine_print_params(machine_t const *m) {
  printf(BGRN "Machine parameters\n" CRESET);
  printf(BBLK "C-CNC:A:         " CRESET "%f\n", m->A);
  printf(BBLK "C-CNC:tq:        " CRESET "%f\n", m->tq);
  printf(BBLK "C-CNC:max_error: " CRESET "%f\n", m->max_error);
}

#ifdef MACHINE_MAIN

int main(int argc, char const *argv[]) {
  machine_t *m = machine_new(argv[1]);
  if (!m)
    exit(EXIT_FAILURE);
  machine_print_params(m);
  machine_free(m);
  return 0;
}

#endif
