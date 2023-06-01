#include "queue.h"

// Per capirci qualcosa, non è una queue dinamica, è come se tutti gli elementi
// fossero già istanziati, li andiamo semplicemente a scrivere e sovrascrivere
// Da quello che ho capito head e tail non hanno indici fissi tipo uno 0 e
// l'altro la dimensione massima, sono valori variabili nel range 0-max-size
// riscalati ogni volta con % per max-size

void Queue_Initialize(Queue_t **fifo) {
  (*fifo) = malloc(sizeof(Queue_t));
  (*fifo)->head = (0); // The () casts automatically the right type
  (*fifo)->tail = (0);
}

void Queue_Destroy(Queue_t **fifo) { free((*fifo)); }

bool Queue_is_full(Queue_t **fifo) {
  // Here we are checking that if we add another element to the head and this
  // element is equal to the tail then it's full. It's the tail because we are
  // using the % operator: if an array is full with 8 elements then in a fifo
  // the head is 7 and the tail is 0, and queue_size is 8, if we add another
  // element than the head becomes 8 -> 8 % 8 = 0 = tail -> it's full
  return (bool)(((*fifo)->head + 1) % QUEUE_SIZE == (*fifo)->tail);
}

bool Queue_is_empty(Queue_t **fifo) {
  // same reasonment as before, we just have to check if head = tails -> empty
  // queue
  return (bool)((*fifo)->head == (*fifo)->tail);
}

bool Queue_Push(Queue_t **fifo, queue_element_t *element) {
  // If we want to push another element we have to make sure it is not already
  // full
  if (Queue_is_full(fifo)) {
    return false;
  }

  // Now we're putting in tmp_element the actual head of the queue and we're
  // assigning the values passed as arguments
  queue_element_t *tmp_element = &(*fifo)->queue[(*fifo)->head];
  tmp_element->id = element->id;
  tmp_element->size = element->size;
  // Loop used to iterate through every byte of the payload and copy it
  for (int i = 0; i < element->size; i++) {
    tmp_element->payload[i] = element->payload[i];
  }

  // Once we have finished we increase the counter of the head, so next time we
  // add a element we're not overwriting old elements
  // We use the module % to keep the head index between 0 and 19, so everytime
  // we fill up the head the counter will start again from 0 and so on
  (*fifo)->head = ((*fifo)->head + 1) % QUEUE_SIZE;

  return true;
}

bool Queue_Pop(Queue_t **fifo, queue_element_t *element) {
  // Similar steps to push
  if (Queue_is_empty(fifo)) {
    return false;
  }

  // Instead of copying the element inside the temporary element we do the
  // opposite
  // We're copying the queue element at tail index
  queue_element_t *tmp_element = &(*fifo)->queue[(*fifo)->tail];
  element->id = tmp_element->id;
  element->size = tmp_element->size;
  for (int i = 0; i < tmp_element->size; i++) {
    element->payload[i] = tmp_element->payload[i];
  }
  // Doing so we pass the pointer to the element we are defining outside the
  // queue, we copy it's content in another temporary object inside the queues

  // Increase tail index
  (*fifo)->tail = ((*fifo)->tail + 1) % QUEUE_SIZE;

  return true;
}