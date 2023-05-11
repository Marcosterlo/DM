/******************************************************************************
Finite State Machine
Project: VM
Description: Finite state machine for vending machine

Generated by gv_fsm ruby gem, see https://rubygems.org/gems/gv_fsm
gv_fsm version 0.3.4
Generation date: 2023-05-04 16:00:44 +0200
Generated from: fsm_vending.dot
The finite state machine has:
  7 states
  3 transition functions
Functions and types have been generated with prefix "vm_"
******************************************************************************/

#ifndef FSM_H
#define FSM_H
#include <stdlib.h>

// State data object
// By default set to void; override this typedef or load the proper
// header if you need
typedef struct vm_state_data {
  int counts[4];
  int coins;
  int total_cash;
  int failed_line;
  int selection;
} vm_state_data_t;

// NOTHING SHALL BE CHANGED AFTER THIS LINE!

// List of states
typedef enum {
  VM_STATE_INIT = 0,  
  VM_STATE_IDLE,  
  VM_STATE_COIN_IN,  
  VM_STATE_STOP,  
  VM_STATE_RETURN_COIN,  
  VM_STATE_SELECTION,  
  VM_STATE_DISPENSING,  
  VM_NUM_STATES,
  VM_NO_CHANGE
} vm_state_t;

// State human-readable names
extern const char *vm_state_names[];

// State function and state transition prototypes
typedef vm_state_t state_func_t(vm_state_data_t *data);
typedef void transition_func_t(vm_state_data_t *data);

// State functions

// Function to be executed in state init
// valid return states: VM_STATE_IDLE
vm_state_t vm_do_init(vm_state_data_t *data);

// Function to be executed in state idle
// valid return states: VM_NO_CHANGE, VM_STATE_IDLE, VM_STATE_COIN_IN, VM_STATE_STOP
vm_state_t vm_do_idle(vm_state_data_t *data);

// Function to be executed in state coin_in
// valid return states: VM_NO_CHANGE, VM_STATE_COIN_IN, VM_STATE_RETURN_COIN, VM_STATE_SELECTION
vm_state_t vm_do_coin_in(vm_state_data_t *data);

// Function to be executed in state stop
// valid return states: VM_NO_CHANGE
vm_state_t vm_do_stop(vm_state_data_t *data);

// Function to be executed in state return_coin
// valid return states: VM_STATE_IDLE
vm_state_t vm_do_return_coin(vm_state_data_t *data);

// Function to be executed in state selection
// valid return states: VM_NO_CHANGE, VM_STATE_SELECTION, VM_STATE_DISPENSING
vm_state_t vm_do_selection(vm_state_data_t *data);

// Function to be executed in state dispensing
// valid return states: VM_NO_CHANGE, VM_STATE_IDLE, VM_STATE_RETURN_COIN, VM_STATE_DISPENSING
vm_state_t vm_do_dispensing(vm_state_data_t *data);


// List of state functions
extern state_func_t *const vm_state_table[VM_NUM_STATES];


// Transition functions
void vm_reset(vm_state_data_t *data);
void vm_disable_line(vm_state_data_t *data);

// Table of transition functions
extern transition_func_t *const vm_transition_table[VM_NUM_STATES][VM_NUM_STATES];

// state manager
vm_state_t vm_run_state(vm_state_t cur_state, vm_state_data_t *data);

#endif
