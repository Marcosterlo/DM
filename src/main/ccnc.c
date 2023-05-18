#include "../defines.h"
#include "../fsm.h"
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <sched.h>

// Better to do whenever we use a name more than once
#define INI_FILE "machine.ini"

// Define empty signal handler
void handler(int signal) {}

int main(int argc, char const *argv[]) {
  // Definition of struct
  struct itimerval itv;
  int rc;
  ccnc_state_data_t state_data = {
      .ini_file = INI_FILE,
      .prog_file = (char *)argv[1],
      .machine = machine_new(INI_FILE),
      .program = NULL,
  };
  ccnc_state_t cur_state = CCNC_STATE_INIT;

  // Check to see if the machine is created correctly
  if (!state_data.machine) {
    eprintf("Error initializing the machine\n");
    exit(EXIT_FAILURE);
  }

  // Delta t imported by configuration file
  useconds_t dt = machine_tq(state_data.machine) * 1E6;
  // to convert second into microseconds
  // Delta t max
  useconds_t dt_max = dt * 10;
// Doing so we typically wait for dt but no more than 10*dt

// On Linux, set the scheduler and the priority
#ifdef __linux__
  struct sched_param param = {.sched_priority = 80};
  rc = sched_setscheduler(getpid(), SCHED_FIFO, &param);
  if (rc) {
    perror("Error (need sudo?): ");
    exit(EXIT_FAILURE);
  }
#endif

  // Set the timer
  itv.it_interval.tv_sec = 0;
  itv.it_interval.tv_usec = dt;
  itv.it_value.tv_sec = 0;
  itv.it_value.tv_usec = dt;

  // Install signal handler
  signal(SIGALRM, handler);

  // Load the timer mechanism
  if (setitimer(ITIMER_REAL, &itv, NULL)) {
    eprintf("Could not set timer\n");
    exit(EXIT_FAILURE);
  }

  // System logging
  openlog("SM", LOG_PID | LOG_PERROR, LOG_USER);
  syslog(LOG_INFO, "Starting SM");

  //======================== MAIN LOOP =========================================
  do {
    cur_state = ccnc_run_state(cur_state, &state_data);
    // We want to take the time interval from the machine object but if in init
    // we can't initialize it we would refer to a non existing object causing a
    // segmentation fault error. To solve the problem we initialize the machine
    // here.

    // Here we would need to implement the timer. We choose the approach with
    // the OS signals
    if (usleep(dt_max) == 0) {
      // We waited the whole dt_max -> we couldn't complete the loop in designated time
      wprintf("Did not complete the loop in less than %d\n", dt_max);
    }
    // If a signal is delivered to the process the usleep returns an error, -1
    // from the man,

  } while (cur_state != CCNC_STATE_STOP);
  // The memory leak happened here, when the stop condition were met initially
  // the line was: ccnc_run_state(cur_state, NULL);
  // Now passing the state_data the function called in the stop state can
  // successfully access to state_data and clean the machine and program
  // instance that it contains
  ccnc_run_state(cur_state, &state_data);
  return 0;
}