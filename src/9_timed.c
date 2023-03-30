#include <signal.h> // we are able to catch signals, something managed by the operating system used  or communicating between processes
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h> // these includes utility and definition for time, date time etc...
#include <unistd.h> // some utilities like sleep() function
// to get a list of signals searching for signal.h on browser we get some
// documentation, some of the most used are: SIGKILL to kill a process or
// SIGTERM, today we use SIGALARM. By using htop we can see the list of
// processes, we can send to signals to the process like SIGKILL via F9, can
// choose the signal to send the process

// Function declaration
void handler(int signal);

int main() {

  // Variable definition
  int i = 0;
  double t0 = 0, t = 0, dt = 0;

  // Timer struct
  struct itimerval itv; // used to configure the timer, used to trigger
                        // something inside the application
  struct timespec ts;   // the struct stores the actual timer

  // Timer configuration
  itv.it_interval.tv_sec = 0;
  itv.it_interval.tv_usec = 5000; // 5ms
  // These are the delta times between two events occuring
  itv.it_value.tv_sec = 0;     // timer initial value
  itv.it_value.tv_usec = 5000; // 5ms -> the first occurence happen after 5ms

  // Let's now catch out ALARM signal
  signal(SIGALRM, handler);

  // Timer set
  if (setitimer(ITIMER_REAL, &itv, NULL)) {
    printf("Timer setup failed!\n");
    return 0;
  }

  // Read actual time -> For futher information check docs
  clock_gettime(CLOCK_MONOTONIC, &ts); // Vscode da errore ma il compilatore no
  t0 = ts.tv_sec + ts.tv_nsec / 1.0E9; // divide the number of nano seconds by
                                       // one million to obtain seconds.
  printf("tv_sec: %ld, tv_nsec: %ld\n", ts.tv_sec, ts.tv_nsec);
  printf("t0: %.9f\n", t0);

  // CSV like header
  printf("n, dt\n");
  for (i = 0; i < 100; i++) {
    sleep(1); // sleeps for 1 seconds unless a SIGALRM signal arrives first

    // Getting the time
    clock_gettime(CLOCK_MONOTONIC, &ts);
    t = ts.tv_sec + ts.tv_nsec / 1.0E9;
    dt = t - t0;
    t0 = t;
    printf("%d, %f\n", i, dt);
    // This prints every event with the corresponding elapsed time between every
    // sleep function call and interruption by the SIGALRM signal our timer
    // generates
  }

  return 0;
}

// Function definition
void handler(int signal) {}