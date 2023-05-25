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
#include <mosquitto.h>

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
data_t machine_A(machine_t const *m);
data_t machine_tq(machine_t const *m);
data_t machine_max_error(machine_t const *m);
data_t machine_error(machine_t const *m);
data_t machine_max_feed(machine_t const *m);
data_t machine_rt_pacing(machine_t const *m);
point_t *machine_zero(machine_t const *m);
point_t *machine_setpoint(machine_t const *m);
point_t *machine_position(machine_t const *m);

// Methods, public functions to deal with the class
void machine_print_params(machine_t const *m);

// MQTT-related
// Callback definition
typedef void (*machine_on_message)(struct mosquitto *mqt, void *userdata,
                                   struct mosquitto_message const *msg);

int machine_connect(machine_t *m, machine_on_message callback);
// We add the rapid flag to tell wether we have to implement a rapid or
// interpolation motion
int machine_sync(machine_t *m, int rapid);
// Listening = registering as a subscriber in MQTT Protocol
int machine_listen_start(machine_t *m);
int machine_listen_stop(machine_t *m);
void machine_disconnect(machine_t *m);

#endif // MACHINE_H
