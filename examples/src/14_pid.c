#include "pid_controller.h"

// 1 DoF spring-damper model parameters
#define MASS 20.0f
#define K_SPRING 50.0f
#define C_DAMPER 10.0f

// Simulation parameters
#define TIME_STEP 0.01f  // seconds
#define NUM_STEPS (2000) // usually interpreted as integer

// Macro definition to saturate a value between two boundaries
#define PID_OUTPUT_SATURATE(x, lower, upper)                                   \
  ((x) < (lower) ? (lower) : ((x) > (upper) ? (upper) : (x)))

// Integrate one step of the spring and damper model
void SpringDamperModel_Compute(float input_force, float *position,
                               float *velocity) {
  // Force equilibrium
  float force =
      input_force - (K_SPRING * (*position)) - (C_DAMPER * (*velocity));
  float acceleration = force / MASS;

  (*position) += (*velocity) * TIME_STEP;
  (*velocity) += acceleration * TIME_STEP;
}

int main() {
  PID_controller_t *pid = {0};
  PID_gains_t gains = {
      .Kp = 100.0f,
      .Ki = 40.0f, // The integral will remove the steady state error
      .Kd = 0.0f,  // Will increase the step response
  };
  // Setpoint definition
  float set_point = 10.0f;
  // Initial conditions definition
  float position = 5.0f, velocity = 0.0f, force = 0.0f;

  // Pid initialization
  PID_Initialize(&pid, gains, TIME_STEP);

  // Set_point setup
  PID_Set_SetPoint(&pid, set_point);

  // Header of csv file:
  printf("Iteration,Position,Velocity,Force,Set point\n");

  // Simulation
  for (int i = 0; i < NUM_STEPS; i++) {
    force = PID_Compute(&pid, position);
    force = PID_OUTPUT_SATURATE(force, -1000.0f, 1000.0f);
    SpringDamperModel_Compute(force, &position, &velocity);
    printf("%d, %.3f, %.3f, %.3f, %.3f\n", i, position, velocity, force,
           set_point);
  }

  return 0;
}