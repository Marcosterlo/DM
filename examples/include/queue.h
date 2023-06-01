#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Macro for defining number of queue elements
#define QUEUE_SIZE (20)
// Number of payload elements
#define PAYLOAD_SIZE (8) 

// Queue element coming from any protocol (bluetooth, mqtt, serial...)
typedef struct {
  uint8_t id;                     // Element identifier
  uint8_t payload[PAYLOAD_SIZE];  // Actual data (payload)
  uint8_t size;                   // Size of my payload 
} queue_element_t;

// This is the description of my queue
typedef struct {
  queue_element_t queue[QUEUE_SIZE]; // Array
  uint8_t head, tail; // Head and tail index of my queue
} Queue_t;

//   ___                                         _   _               _     
//  / _ \ _   _  ___ _   _  ___   _ __ ___   ___| |_| |__   ___   __| |___ 
// | | | | | | |/ _ \ | | |/ _ \ | '_ ` _ \ / _ \ __| '_ \ / _ \ / _` / __|
// | |_| | |_| |  __/ |_| |  __/ | | | | | |  __/ |_| | | | (_) | (_| \__ \
//  \__\_\\__,_|\___|\__,_|\___| |_| |_| |_|\___|\__|_| |_|\___/ \__,_|___/
//

// Strobbe notation on functions: Uppercase everywhere in public methos, private or utilities functions are lowercase

// If the queue is very big, we need to process a lot of data it's better to store it into heap, in our case the max size is 20*8 bytes, very small so we can store it into the stack
void Queue_Initialize(Queue_t **fifo);
void Queue_Destroy(Queue_t **fifo);
// Utility  functions
// It should measure the distance between the head and the tail, we want to test that if we add another object than its counter would be the tail, in this case it is full
bool Queue_is_full(Queue_t **fifo);
// Same thing but to check if it's empty
bool Queue_is_empty(Queue_t **fifo);
// the boolean return value should tell if we were able to push/pop or not
bool Queue_Push(Queue_t **fifo, queue_element_t *element);
bool Queue_Pop(Queue_t **fifo, queue_element_t *element);


                                                                         