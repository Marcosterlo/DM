#include "queue.h"

void print_element(queue_element_t *element) {
  printf("id:       %u\n", element->id);
  printf("size:     %u\n", element->size);
  printf("payload:  [");
  for (int i=0; i<element->size; i++) {
    printf(" 0x%02x ", element->payload[i]);
  }
  printf("]\n");
}

int main() {

  // Queue definition
  Queue_t *fifo = NULL;

  // Initializer of queue
  Queue_Initialize(&fifo);

  // Define temporary element
  queue_element_t element = {0}; // We used a null initializer
  element.id = 50;
  element.size = 3;
  element.payload[0] = 1;
  element.payload[1] = 2;
  element.payload[2] = 3;

  // Push the element
  Queue_Push(&fifo, &element);

  queue_element_t new_element = {0};
  Queue_Pop(&fifo, &new_element);

  // Check if element == new_element
  print_element(&new_element);

  // Let's test pushing more than 20 elements without popping
  for (int i=0; i<100; i++) {
    element.id = i; 
    // be careful that id is uint8_t, i should be lesser than 255
    if (!Queue_Push(&fifo, &element)) {
      printf("Queue_Push break at index %d\n", i);
      break;
    }
  }

  // Destroy queue
  Queue_Destroy(&fifo);

  return 0;
}