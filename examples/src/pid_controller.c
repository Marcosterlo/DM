#include "pid_controller.h"

void PID_Initialize(PID_controller_t **pid, PID_gains_t gains,
                    float sample_time) {
  (*pid) = malloc(
      sizeof(PID_controller_t)); // Everything initially put to 0 due to malloc
  (*pid)->gains = gains;
  (*pid)->sample_time = sample_time;
}

void PID_Set_SetPoint(PID_controller_t **pid, float set_point) {
  (*pid)->set_point = set_point;
}

float PID_Compute(PID_controller_t **pid, float input) {

  // Error computation
  float error = (*pid)->set_point - input;
  float d_error =
      (error - (*pid)->prev_error) / (*pid)->sample_time; // Error derivative
  (*pid)->int_error += error * (*pid)->sample_time;

  // PID terms computation
  float p_term = (*pid)->gains.Kp * error;              // P
  float i_term = (*pid)->gains.Ki * (*pid)->int_error;  // I
  float d_term = (*pid)->gains.Kd * d_error;            // D

  // Control signal computation
  (*pid)->output = p_term + i_term + d_term;

  // Update of previous error
  (*pid)->prev_error = error;

  return (*pid)->output;
}