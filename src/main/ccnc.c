#include "../defines.h"
#include "../fsm.h"
#include <unistd.h>

int main(int argc, char const *argv[]) {
  ccnc_state_data_t state_data = {
      .ini_file = "machine.ini",
      .prog_file = (char *)argv[1],
      .machine = NULL,
      .program = NULL,
  };
  ccnc_state_t cur_state = CCNC_STATE_INIT;
  openlog("SM", LOG_PID | LOG_PERROR, LOG_USER);
  syslog(LOG_INFO, "Starting SM");
  do {
    cur_state = ccnc_run_state(cur_state, &state_data);
    // Here we would need to implement the timer
    usleep(5000); // We put 5ms for the moment
  } while (cur_state != CCNC_STATE_STOP);
  // The memory leak happened here, when the stop condition were met initially
  // the line was: ccnc_run_state(cur_state, NULL);
  // Now passing the state_data the function called in the stop state can
  // successfully access to state_data and clean the machine and program
  // instance that it contains
  ccnc_run_state(cur_state, &state_data);
  return 0;
}