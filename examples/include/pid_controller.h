#include <stdlib.h>
#include <stdio.h>

// We need to store at least the 3 gain numbers
// We need to store the integral part of the error in memory, the other components are temporary

// PID gains struct
typedef struct {
  float Kp, Ki, Kd;
} PID_gains_t;

// PID struct
typedef struct {
  PID_gains_t gains; // Collect actual PID gains
  float sample_time; // PID integration time
  float int_error;   // Collect the error over time
  // Instead of creating another variable which is the derivative of the error I simply store the previous error, compare with actual error, dividing by sample_time and find the derivative error
  float prev_error;
  float output;      // PID output control signal
  float set_point;   // Actual PID set point
} PID_controller_t;

// PID initialization method
void PID_Initialize(PID_controller_t **pid, PID_gains_t gains, float sample_time);

// Set point update method
void PID_Set_SetPoint(PID_controller_t **pid, float set_point);

// Function that must be run every sample time (PID update/compute), we want it to return the output
float PID_Compute(PID_controller_t **pid, float input);