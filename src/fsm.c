/******************************************************************************
Finite State Machine
Project: C-CNC
Description: Finite state machine for C-CNC

Generated by gv_fsm ruby gem, see https://rubygems.org/gems/gv_fsm
gv_fsm version 0.3.4
Generation date: 2023-05-11 12:44:01 +0200
Generated from: src/fsm.dot
The finite state machine has:
  7 states
  5 transition functions
Functions and types have been generated with prefix "ccnc_"
******************************************************************************/

#include "fsm.h"
#include "block.h"
#include "defines.h"
#include "point.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// Install signal handler:
// SIGINT requests a transition to state stop
// It does it by changing the global variable _exit_request
#include <signal.h>
static int _exit_request = 0;
static void signal_handler(int signal) {
  if (signal == SIGINT) {
    _exit_request = 1;
    syslog(LOG_WARNING, "[FSM] SIGINT transition to stop");
  }
}

// Function described in fsm.c in examples in c-cnc23 by bosetti
static char read_key() {
  char key;
  struct termios old_tio, new_tio;
  // save current terminal settings
  tcgetattr(STDIN_FILENO, &old_tio);
  // copy setting into new structure
  new_tio = old_tio;
  // disable caching
  cfmakeraw(&new_tio);
  // set new settings
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
  // wait for keypress
  key = getchar();
  // reset initial temrinal setings
  tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
  return key;
}

// SEARCH FOR Your Code Here FOR CODE INSERTION POINTS!

// GLOBALS
// State human-readable names
const char *ccnc_state_names[] = {"init",         "idle",      "stop",
                                  "load_block",   "no_motion", "rapid_motion",
                                  "interp_motion"};

// List of state functions
state_func_t *const ccnc_state_table[CCNC_NUM_STATES] = {
    ccnc_do_init,          // in state init
    ccnc_do_idle,          // in state idle
    ccnc_do_stop,          // in state stop
    ccnc_do_load_block,    // in state load_block
    ccnc_do_no_motion,     // in state no_motion
    ccnc_do_rapid_motion,  // in state rapid_motion
    ccnc_do_interp_motion, // in state interp_motion
};

// Table of transition functions
transition_func_t
    *const ccnc_transition_table[CCNC_NUM_STATES][CCNC_NUM_STATES] = {
        /* states:           init             , idle             , stop ,
           load_block       , no_motion        , rapid_motion     ,
           interp_motion     */
        /* init          */ {NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        /* idle          */ {NULL, NULL, NULL, ccnc_reset, NULL, NULL, NULL},
        /* stop          */ {NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        /* load_block    */
        {NULL, NULL, NULL, NULL, NULL, ccnc_begin_rapid, ccnc_begin_interp},
        /* no_motion     */ {NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        /* rapid_motion  */
        {NULL, NULL, NULL, ccnc_end_rapid, NULL, NULL, NULL},
        /* interp_motion */
        {NULL, NULL, NULL, ccnc_end_interp, NULL, NULL, NULL},
};

/*  ____  _        _
 * / ___|| |_ __ _| |_ ___
 * \___ \| __/ _` | __/ _ \
 *  ___) | || (_| | ||  __/
 * |____/ \__\__,_|\__\___|
 *
 *   __                  _   _
 *  / _|_   _ _ __   ___| |_(_) ___  _ __  ___
 * | |_| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 * |  _| |_| | | | | (__| |_| | (_) | | | \__ \
 * |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
 */

// Function to be executed in state init
// valid return states: CCNC_STATE_IDLE, CCNC_STATE_STOP
// The structure ccnc_state_data_t must holds all the data we need
ccnc_state_t ccnc_do_init(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_STATE_IDLE;
  point_t *sp = NULL, *zero = NULL;
  signal(SIGINT, signal_handler);

  // syslog is a way to write messages into the OS log facility, 1st argument is
  // type of log, 2nd arguument is the message, other arguments are used like
  // printf to substitute values, it's useful for debugging and can be disabled
  // later
  syslog(LOG_INFO, "[FSM] In state init");
  /* Your Code Here */

  // PART EDITED BY MARCO

  // 1. print out software version
  fprintf(stderr, "C-CNC version %s, %s build\n", VERSION, BUILD_TYPE);

  // 2. connect to the machine
  // edit: we already created the machine instance in ccnc.c so either we assume
  // the machine already initialized or we check if it has been initialized and
  // we create it eventually, in this way the code is more robust
  if (!data->machine) {
    data->machine = machine_new(data->ini_file);
  }
  if (!data->machine) {
    next_state = CCNC_STATE_STOP;
    goto next_state;
  }
  if (machine_connect(data->machine, NULL) != EXIT_SUCCESS) {
    next_state = CCNC_STATE_STOP;
    goto next_state;
  }

  // 3. load and parse g-code
  data->program = program_new(data->prog_file);
  if (!data->program) {
    next_state = CCNC_STATE_STOP;
    goto next_state;
  }
  if (!program_parse(data->program, data->machine)) {
    next_state = CCNC_STATE_STOP;
    goto next_state;
  }

  // 4. print the parsed program
  fprintf(stderr, "Current program: %s\n", data->prog_file);
  program_print(data->program, stderr);

  // 5. sync the machine position to zero (initial point of the machine tool)
  sp = machine_setpoint(data->machine);
  zero = machine_zero(data->machine);
  point_set_xyz(sp, point_x(zero), point_y(zero), point_z(zero));
  machine_sync(data->machine, 1); // This is a rapid motion

  // 6. display total time and length of the program
  fprintf(stderr, BGRN "Total length: %f\n" CRESET,
          program_tot_length(data->program, data->machine));
  fprintf(stderr, BGRN "Total time: %f\n" CRESET,
          program_time(data->program, data->machine));

next_state: // END PART EDITED BY MARCO
  switch (next_state) {
  case CCNC_STATE_IDLE:
  case CCNC_STATE_STOP:
    break;
  default:
    syslog(LOG_WARNING,
           "[FSM] Cannot pass from init to %s, remaining in this state",
           ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  return next_state;
}

// Function to be executed in state idle
// valid return states: CCNC_NO_CHANGE, CCNC_STATE_IDLE, CCNC_STATE_LOAD_BLOCK,
// CCNC_STATE_STOP SIGINT triggers an emergency transition to stop
ccnc_state_t ccnc_do_idle(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_NO_CHANGE;
  char key;

  syslog(LOG_INFO, "[FSM] In state idle");

  // PART EDITED BY MARCO
  // Steps:
  // 1. Wait for keypress and command according state transition
  fprintf(stderr, "Press " BGRN "spacebar" CRESET " to run, " BRED "'q'" CRESET
                  " to quit\n");
  key = read_key();
  switch (key) {
  case ' ':
    next_state = CCNC_STATE_LOAD_BLOCK;
    break;
  case 'q':
  case 'Q':
    next_state = CCNC_STATE_STOP;
    break;
  default:
    break;
  }

  // 2. Reset times (total time and block time)
  data->t_blk = data->t_tot = 0;

  // END PART EDITED BY MARCO

  switch (next_state) {
  case CCNC_NO_CHANGE:
  case CCNC_STATE_IDLE:
  case CCNC_STATE_LOAD_BLOCK:
  case CCNC_STATE_STOP:
    break;
  default:
    // This log is used to warn when the state is not one we're supposed to go
    // to from the current state
    syslog(LOG_WARNING,
           "[FSM] Cannot pass from idle to %s, remaining in this state",
           ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  // SIGINT transition override
  if (_exit_request)
    next_state = CCNC_STATE_STOP;

  return next_state;
}

// Function to be executed in state stop
// valid return states: CCNC_NO_CHANGE
ccnc_state_t ccnc_do_stop(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_NO_CHANGE;

  syslog(LOG_INFO, "[FSM] In state stop");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 0. Reset signal handler
  signal(SIGINT, SIG_DFL); // We reset the sigint if we came in stop using it

  // 1. Disconnecting
  wprintf("Disconnect...\n");
  if (data->machine)
    machine_disconnect(data->machine);

  wprintf("Clean up...\n");
  // 2. Free resources
  if (data->program)
    program_free(data->program);
  if (data->machine)
    machine_free(data->machine);
  wprintf("done.\n");

  // END PART EDITED BY MARCO

  switch (next_state) {
  case CCNC_NO_CHANGE:
    break;
  default:
    syslog(LOG_WARNING,
           "[FSM] Cannot pass from stop to %s, remaining in this state",
           ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  return next_state;
}

// Function to be executed in state load_block
// valid return states: CCNC_STATE_IDLE, CCNC_STATE_NO_MOTION,
// CCNC_STATE_RAPID_MOTION, CCNC_STATE_INTERP_MOTION
ccnc_state_t ccnc_do_load_block(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_STATE_IDLE;
  block_t *b = NULL;
  data_t tq = machine_tq(data->machine);

  syslog(LOG_INFO, "[FSM] In state load_block");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 1. Get and print the next block
  b = program_next(data->program);
  if (!b) {
    // NULL because program ended or program empty, we go back to idle in both
    // cases
    next_state = CCNC_STATE_IDLE;
    goto next_state;
  }
  block_print(b, stderr);

  // 2. Depending on block type, select the next state
  switch (block_type(b)) {
  case NO_MOTION:
    next_state = CCNC_STATE_NO_MOTION;
    break;
  case RAPID:
    next_state = CCNC_STATE_RAPID_MOTION;
    break;
  case LINE:
  case ARC_CW:
  case ARC_CCW:
    next_state = CCNC_STATE_INTERP_MOTION;
    break;
  default:
    next_state = CCNC_STATE_IDLE;
    break;
  }

  // 3. Increment the total time
  data->t_tot += tq;

  // END PART EDITED BY MARCO

next_state:
  switch (next_state) {
  case CCNC_STATE_IDLE:
  case CCNC_STATE_NO_MOTION:
  case CCNC_STATE_RAPID_MOTION:
  case CCNC_STATE_INTERP_MOTION:
    break;
  default:
    syslog(LOG_WARNING,
           "[FSM] Cannot pass from load_block to %s, remaining in this state",
           ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  return next_state;
}

// Function to be executed in state no_motion
// valid return states: CCNC_STATE_LOAD_BLOCK
ccnc_state_t ccnc_do_no_motion(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_STATE_LOAD_BLOCK;
  data_t tq = machine_tq(data->machine);

  syslog(LOG_INFO, "[FSM] In state no_motion");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 1. Print block number
  fprintf(stderr, "No motion block %zu\n",
          block_n(program_current(data->program)));

  // 2. Increment total time
  data->t_tot += tq;

  // END PART EDITED BY MARCO

  switch (next_state) {
  case CCNC_STATE_LOAD_BLOCK:
    break;
  default:
    syslog(LOG_WARNING,
           "[FSM] Cannot pass from no_motion to %s, remaining in this state",
           ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  return next_state;
}

// Function to be executed in state rapid_motion
// valid return states: CCNC_NO_CHANGE, CCNC_STATE_LOAD_BLOCK,
// CCNC_STATE_RAPID_MOTION SIGINT triggers an emergency transition to stop
ccnc_state_t ccnc_do_rapid_motion(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_NO_CHANGE;
  data_t tq = machine_tq(data->machine);
  block_t *b = program_current(data->program);
  point_t *pos = machine_position(data->machine);

  syslog(LOG_INFO, "[FSM] In state rapid_motion");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 1. Sync machine
  machine_sync(data->machine, 1);

  // 2. Exit this state if the error is small enough
  if (machine_error(data->machine) < machine_max_error(data->machine)) {
    next_state = CCNC_STATE_LOAD_BLOCK;
  }

  // 3. CTRL-C may be used for skipping over a rapid block (if we are simulating
  // without a real machine or digital twin we will never receive the error
  // value back)
  if (_exit_request) {
    _exit_request = 0;
    next_state = CCNC_STATE_LOAD_BLOCK;
  }

  // 4. Print position table (to let the user know where we are)
  // The zeros are lambda curv abscissa and velocity only calculated for
  // interpolated blocks
  printf("%lu %d %f %f %f %f %f %f %f %f\n", block_n(b), block_type(b),
         data->t_tot, data->t_blk, 0.0, 0.0, 0.0, point_x(pos), point_y(pos),
         point_z(pos));

  // 5. Print progress percentage bar (ratio between actual error and block
  // length)
  // We have to print something only the first time, we use the transition
  // function, executed only on transition to the state, the first time
  fprintf(stderr, "\b\b\b\b\b\b\b\b");
  fflush(stderr);
  fprintf(stderr, "[%5.1f%%]",
          machine_error(data->machine) / block_length(b) * 100);

  // 6. Increment times
  data->t_blk += tq;
  data->t_tot += tq;

  // END PART EDITED BY MARCO

  switch (next_state) {
  case CCNC_NO_CHANGE:
  case CCNC_STATE_LOAD_BLOCK:
  case CCNC_STATE_RAPID_MOTION:
    break;
  default:
    syslog(LOG_WARNING,
           "[FSM] Cannot pass from rapid_motion to %s, remaining in this state",
           ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  // SIGINT transition override
  if (_exit_request)
    next_state = CCNC_STATE_STOP;

  return next_state;
}

// Function to be executed in state interp_motion
// valid return states: CCNC_NO_CHANGE, CCNC_STATE_LOAD_BLOCK,
// CCNC_STATE_INTERP_MOTION SIGINT triggers an emergency transition to stop
ccnc_state_t ccnc_do_interp_motion(ccnc_state_data_t *data) {
  ccnc_state_t next_state = CCNC_NO_CHANGE;
  data_t tq = machine_tq(data->machine);
  data_t lambda, feed;
  block_t *b = program_current(data->program);
  point_t *sp = NULL;

  syslog(LOG_INFO, "[FSM] In state interp_motion");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 1. Calculate lambda and interpolate position
  lambda = block_lambda(b, data->t_blk, &feed);
  sp = block_interpolate(b, lambda);

  // 2. Print position table
  printf("%lu %d %f %f %f %f %f %f %f %f\n", block_n(b), block_type(b),
         data->t_tot, data->t_blk, lambda, lambda * block_length(b), feed,
         point_x(sp), point_y(sp), point_z(sp));

  // 3. Print progress indicator
  fprintf(stderr, "\b\b\b\b\b\b\b\b");
  fflush(stderr);
  fprintf(stderr, "[%5.1f%%]", lambda * 100);

  // 4. Sync machine
  machine_sync(data->machine, 0);

  // 5. Check if block is done
  if (data->t_blk >= block_dt(b) + tq / 10.0) {
    next_state = CCNC_STATE_LOAD_BLOCK;
  }

  // 6. Increment times
  data->t_blk += tq;
  data->t_tot += tq;

  // END PART EDITED BY MARCO

  switch (next_state) {
  case CCNC_NO_CHANGE:
  case CCNC_STATE_LOAD_BLOCK:
  case CCNC_STATE_INTERP_MOTION:
    break;
  default:
    syslog(
        LOG_WARNING,
        "[FSM] Cannot pass from interp_motion to %s, remaining in this state",
        ccnc_state_names[next_state]);
    next_state = CCNC_NO_CHANGE;
  }

  // SIGINT transition override
  if (_exit_request)
    next_state = CCNC_STATE_STOP;

  return next_state;
}

/*  _____                    _ _   _
 * |_   _| __ __ _ _ __  ___(_) |_(_) ___  _ __
 *   | || '__/ _` | '_ \/ __| | __| |/ _ \| '_ \
 *   | || | | (_| | | | \__ \ | |_| | (_) | | | |
 *   |_||_|  \__,_|_| |_|___/_|\__|_|\___/|_| |_|
 *
 *   __                  _   _
 *  / _|_   _ _ __   ___| |_(_) ___  _ __  ___
 * | |_| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 * |  _| |_| | | | | (__| |_| | (_) | | | \__ \
 * |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
 */

// This function is called in 1 transition:
// 1. from idle to load_block
void ccnc_reset(ccnc_state_data_t *data) {
  syslog(LOG_INFO, "[FSM] State transition ccnc_reset");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 1. Reset both timers
  data->t_blk = data->t_tot = 0;

  // 2. Print header line on stdout
  printf("n type t_tot t_blk lambda s feed x y z\n");

  // END PART EDITED BY MARCO
}

// This function is called in 1 transition:
// 1. from load_block to rapid_motion
void ccnc_begin_rapid(ccnc_state_data_t *data) {
  block_t *b = program_current(data->program);
  point_t *sp = machine_setpoint(data->machine);
  point_t *target = block_target(b);

  syslog(LOG_INFO, "[FSM] State transition ccnc_begin_rapid");
  /* Your Code Here */
  // PART EDITED BY MARCO

  // Steps
  // 1. Reset only the block timer
  data->t_blk = 0;

  // 2. Start listening to MQTT status updates
  machine_listen_start(data->machine);

  // 3. Set final position and set point
  point_set_xyz(sp, point_x(target), point_y(target), point_z(target));
  machine_sync(data->machine, 1);

  // 4. Print INITIAL values for progress string (8 chars)
  fprintf(stderr, "Rapid block length: %f\n", block_length(b));
  fprintf(stderr, "[  0.0%%]");

  // END PART EDITED BY MARCO
}

// This function is called in 1 transition:
// 1. from load_block to interp_motion
void ccnc_begin_interp(ccnc_state_data_t *data) {
  syslog(LOG_INFO, "[FSM] State transition ccnc_begin_interp");
  /* Your Code Here */
  // PART EDITED BY MARCO

  data->t_blk = 0;
  fprintf(stderr, "[  0.0%%]");

  // END PART EDITED BY MARCO
}

// This function is called in 1 transition:
// 1. from rapid_motion to load_block
void ccnc_end_rapid(ccnc_state_data_t *data) {
  syslog(LOG_INFO, "[FSM] State transition ccnc_end_rapid");
  /* Your Code Here */
  // PART EDITED BY MARCO

  fprintf(stderr, "\b\b\b\b\b\b\b\b\b");
  machine_listen_stop(data->machine);

  // END PART EDITED BY MARCO
}

// This function is called in 1 transition:
// 1. from interp_motion to load_block
void ccnc_end_interp(ccnc_state_data_t *data) {
  syslog(LOG_INFO, "[FSM] State transition ccnc_end_interp");
  /* Your Code Here */
  fprintf(stderr, "\b\b\b\b\b\b\b\b\b");
}

/*  ____  _        _
 * / ___|| |_ __ _| |_ ___
 * \___ \| __/ _` | __/ _ \
 *  ___) | || (_| | ||  __/
 * |____/ \__\__,_|\__\___|
 *
 *
 *  _ __ ___   __ _ _ __   __ _  __ _  ___ _ __
 * | '_ ` _ \ / _` | '_ \ / _` |/ _` |/ _ \ '__|
 * | | | | | | (_| | | | | (_| | (_| |  __/ |
 * |_| |_| |_|\__,_|_| |_|\__,_|\__, |\___|_|
 *                              |___/
 */

ccnc_state_t ccnc_run_state(ccnc_state_t cur_state, ccnc_state_data_t *data) {
  ccnc_state_t new_state = ccnc_state_table[cur_state](data);
  if (new_state == CCNC_NO_CHANGE)
    new_state = cur_state;
  transition_func_t *transition = ccnc_transition_table[cur_state][new_state];
  if (transition)
    transition(data);
  return new_state;
};

#ifdef TEST_MAIN
#include <unistd.h>
int main() {
  ccnc_state_t cur_state = CCNC_STATE_INIT;
  openlog("SM", LOG_PID | LOG_PERROR, LOG_USER);
  syslog(LOG_INFO, "Starting SM");
  do {
    cur_state = ccnc_run_state(cur_state, NULL);
    sleep(1);
  } while (cur_state != CCNC_STATE_STOP);
  ccnc_run_state(cur_state, NULL);
  return 0;
}
#endif
