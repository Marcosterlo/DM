//   __  __            _     _
//  |  \/  | __ _  ___| |__ (_)_ __   ___
//  | |\/| |/ _` |/ __| '_ \| | '_ \ / _ \
//  | |  | | (_| | (__| | | | | | | |  __/
//  |_|  |_|\__,_|\___|_| |_|_|_| |_|\___|
//
// Machine class

#ifndef MACHINE_H
#define MACHINE_H

#include "defines.h"
#include "point.h" // useful to represent 3d coordinates

// opaque struct definition
typedef struct machine machine_t;

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Lifecycle

machine_t *machine_new(char const *cfg_path);
// We crate passing the name of a configuration file containing all machine
// parameters
void machine_free(machine_t *m);

// Accessors

// Methods, public functions to deal with the class
void machine_print_params(machine_t const *m);

#endif // MACHINE_H