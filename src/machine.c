//   __  __            _     _
//  |  \/  | __ _  ___| |__ (_)_ __   ___
//  | |\/| |/ _` |/ __| '_ \| | '_ \ / _ \
//  | |  | | (_| | (__| | | | | | | |  __/
//  |_|  |_|\__,_|\___|_| |_|_|_| |_|\___|

#include "machine.h"
#include "toml.h"
#include <mqtt_protocol.h>
#include <string.h>

//   ____            _                 _   _
//  |  _ \  ___  ___| | __ _ _ __ __ _| |_(_) ___  _ __  ___
//  | | | |/ _ \/ __| |/ _` | '__/ _` | __| |/ _ \| '_ \/ __|
//  | |_| |  __/ (__| | (_| | | | (_| | |_| | (_) | | | \__ \
//  |____/ \___|\___|_|\__,_|_|  \__,_|\__|_|\___/|_| |_|___/

#define BUFLEN 1024

typedef struct machine {
  data_t A;  // max acceleration
  data_t tq; // quantization step
  data_t max_error, error;
  point_t *zero;
  point_t *setpoint, *position;

  // MQTT-related fields
  char broker_address[BUFLEN]; // Since it's a web address it's usually not long
  int broker_port;
  char pub_topic[BUFLEN];
  char sub_topic[BUFLEN];
  char pub_buffer[BUFLEN];
  struct mosquitto *mqt;         // Stores the mosquitto object
  struct mosquitto_message *msg; // Stores the last received message
  int connecting; // flag to tell wether we're waiting connection or not, if set
                  // to 1 it means we're waiting connection
} machine_t;

// Callbacks declaration
static void on_connect(struct mosquitto *mqt, void *obj, int rc);
static void on_message(struct mosquitto *mqt, void *obj,
                       const struct mosquitto_message *msg);

//   _____                 _   _
//  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
//  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

// Lifecycle ===================================================================

// We crate passing the name of a configuration file containing all machine
// parameters

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
  else {                                                                       \
    strncpy(machine->key, d.u.s, strlen(machine->key));                        \
    free(d.u.s);                                                               \
  }
  // We freed the string as indicated in the header file of toml library

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

  // Block for mosquitto config import
  {
    toml_datum_t d;
    toml_table_t *mqtt = toml_table_in(conf, "MQTT");
    if (!mqtt) {
      wprintf("Missing MQTT section\n");
      goto fail;
    }

    // MACRO CREATION
    T_READ_S(d, m, mqtt, broker_address);
    T_READ_I(d, m, mqtt, broker_port);
    T_READ_S(d, m, mqtt, pub_topic);
    T_READ_S(d, m, mqtt, sub_topic);
  }

  toml_free(conf);

  // Library mosquitto cleanup and initialization
  if (mosquitto_lib_init() != MOSQ_ERR_SUCCESS) {
    eprintf("Could not initialize the mosquitto library\n");
    goto fail;
  }

  // We set the flag to 1, it means we're waiting for connection
  m->connecting = 1;

  return m;

fail:
  machine_free(m);
  return NULL;
}

void machine_free(machine_t *m) {
  assert(m);
  if (m->zero)
    point_free(m->zero);
  if (m->setpoint)
    point_free(m->setpoint);
  if (m->position)
    point_free(m->position);
  if (m->mqt)
    mosquitto_destroy(m->mqt);
  mosquitto_lib_cleanup();
  free(m);
}

// Accessors ===================================================================

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

// MQTT-related
int machine_connect(machine_t *m, machine_on_message callback) {
  assert(m);
  // mosquitto_new requires: 1) id (for debugging purposes only, if NULL passed
  // automatically set), 2) a boolean (1 or 0) clean_session, set to true to
  // clean every precedent message on disconnect from the broker, for us this is
  // a good idea to keep the program lightweight. 3) void *obj, a general user
  // pointer to any callback that is specified
  int count = 0;
  m->mqt = mosquitto_new(NULL, 1, m);
  if (!m->mqt) {
    // perror is used instead of eprintf, suggested way of dealing with errors
    // by mosquitto and many other libraries, whenever they fail they set an
    // error description into a global variable. Perror uses the same variables
    // and attaches it to our description. It's prefereable to use it when using
    // mosquitto. It prints in STDERR
    perror("Could not create MQTT\n");
    return EXIT_FAILURE;
  }
  // Callback set
  mosquitto_connect_callback_set(m->mqt, on_connect);
  mosquitto_message_callback_set(m->mqt, callback ? callback : on_message);
  // Doing so if we pass a null callback the default callback for message will
  // be on_message static function

  // mosquitto_connect arguments:
  // int mosquitto_connect(struct mosquitto *mosq, const char *host, int port,
  // int keepalive)
  if (mosquitto_connect(m->mqt, m->broker_address, m->broker_port, 10) !=
      MOSQ_ERR_SUCCESS) {
    perror("Invalid broker connection parameters\n");
    return EXIT_FAILURE;
  }
  // Wait for the connection to be established (due to asynchronous mosquitto
  // funciton that get queued and don't get executed immediately)
  while (m->connecting) {
    // While we wait for the connection to happen we call mosquitto_loop that
    // must be called frequently, it's the actual function that does all the
    // scheduled network operations, the second argument is the timeout: max
    // number of milliseconds to wait for next operations, -1 means a thousand
    // millisecond (1 second). After 1 second it returns a error. If we try the
    // connection for more than 5 seconds we assume the broker is not available.
    // Typically if the broker is present we will likely wait less than 1
    // seconds and connecting becomes 0 almost instantaneously.
    printf("loop: %d\n", mosquitto_loop(m->mqt, -1, 1));
    if (++count >= 5) {
      eprintf("Could not connect to broker\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int machine_sync(machine_t *m, int rapid) {
  assert(m && m->mqt);
  // Fill up m->pub_buffer with the set point in JSON format
  // {"x":100.2, "y":123, "z",0.0}
  snprintf(m->pub_buffer, BUFLEN,
           "{\"x\":%f, \"y\"%f, \"z\":%f, \"rapid:\":%s}", point_x(m->setpoint),
           point_y(m->setpoint), point_z(m->setpoint),
           rapid ? "true" : "false");
  // send the buffer
  // int mosquitto_publish(struct mosquitto *mosq, int *mid, const char *topic,
  // int payloadlen, const void *payload, int qos, bool retain)
  // We put retain = 0 to not have future subscriber to have this message
  if (mosquitto_publish(m->mqt, NULL, m->pub_topic, strlen(m->pub_buffer),
                        m->pub_buffer, 0, 0) != MOSQ_ERR_SUCCESS) {
    perror("Could not send message\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int machine_listen_start(machine_t *m) {
  assert(m && m->mqt);
  // int mosquitto_subscribe(struct mosquitto *mosq, int *mid, const char *sub,
  // int qos)
  if (mosquitto_subscribe(m->mqt, NULL, m->sub_topic, 0) != MOSQ_ERR_SUCCESS) {
    perror("Could not subscribe\n");
    return EXIT_FAILURE;
  }
  // We set the machine error to 10 times the maximum error, we have a
  // difference to be corrected at the very beginning
  m->error = m->max_error * 10.0;
  wprintf("Subscribed to topic %s\n", m->sub_topic);
  return EXIT_SUCCESS;
}

int machine_listen_stop(machine_t *m) {
  assert(m && m->mqt);
  if (mosquitto_unsubscribe(m->mqt, NULL, m->sub_topic) != MOSQ_ERR_SUCCESS) {
    perror("Could not unsubscribe\n");
    return EXIT_FAILURE;
  }
  wprintf("Unsubscribed from topic %s\n", m->sub_topic);
  return EXIT_SUCCESS;
}

// Calls mosquitto loop to do
void machine_listen_update(machine_t *m) {
  assert(m && m->mqt);
  // 0 as second argument means to not wait anything to update the loop
  if (mosquitto_loop(m->mqt, 0, 1) != MOSQ_ERR_SUCCESS) {
    perror("mosquitto_loop error\n");
  }
}

void machine_disconnect(machine_t *m) {
  assert(m && m->mqt);
  // Since we have a asynchronous network before disconnecting (which is
  // immediate) we want to wait for any pending operation that needs to be still
  // executed
  while (mosquitto_want_write(m->mqt)) {
    // The functions return true if there are pending operations
    mosquitto_loop(m->mqt, 0, 1);
    // Never a good idea to have a loop running at full speed for CPU usage
    usleep(10000); // 10ms wait
  }
  mosquitto_disconnect(m->mqt);
}

// Static functions
static void on_connect(struct mosquitto *mqt, void *obj, int rc) {
  // We know obj is a machine struct type, we cast it
  machine_t *m = (machine_t *)obj;
  if (rc == CONNACK_ACCEPTED) { // Connection acknowledge accepted,
    wprintf("-> Connected to %s:%d\n", m->broker_address, m->broker_port);
    // second argument is message id, third is subtopic string, fourth is
    // quality of service
    if (mosquitto_subscribe(mqt, NULL, m->sub_topic, 0) != MOSQ_ERR_SUCCESS) {
      perror("Could not subscribe\n");
      exit(EXIT_FAILURE);
    }
  }
  // Fail to connect
  else {
    eprintf("-X Connection error: %s\n", mosquitto_connack_string(rc));
    // This function takes rc and return a human readable description of the
    // error
    exit(EXIT_FAILURE);
  }
  // We reset the waiting for connection flag
  m->connecting = 0;
}

static void on_message(struct mosquitto *mqt, void *obj,
                       const struct mosquitto_message *msg) {}

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