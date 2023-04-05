#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Types definition
typedef float data_t;

typedef struct { // 3 floats -> 4 bytes * 3 = 12 bytes size
  data_t x, y, z;
} point_t;

typedef union {
  data_t x, y, z;
  unsigned char str[sizeof(float)]; // 4 bytes size
} another_pt_t;

typedef struct {
  data_t x;
  data_t y;
  data_t z;
  uint16_t u;
} __attribute__((packed))
point2_t; // Theoretically we should expect its size to be 12 + 2 = 14 bytes

// Function declaration
void print_point(point_t *a);
void print_union_point(another_pt_t *a);
void print_array(unsigned char const *str, int len);

int main() {

  // Declare my struct
  point_t my_pt;

  // Declare and initialize
  point_t my_pt1 = {.x = 1, .y = 2, .z = 3};

  // Pointers
  point_t *my_pt1_ptr = &my_pt1;
  print_point(my_pt1_ptr);

  // Let's try to modify the structure
  my_pt1.x = 46;
  my_pt1_ptr->y = 35; // 2 alternatives
  print_point(&my_pt1);

  printf("The size of my_pt1 is: %lu\n", sizeof(my_pt1));
  printf("The size of my_pt1_ptr is: %lu\n", sizeof(my_pt1_ptr));

  // It's always better to pass pointers rather than entire structures cause,
  // even though this is not the case, they can get very big in memory, a
  // pointer instead is rather small, usually just 8 bytes containing the
  // address

  // Let's print the size of point2_t
  printf("The size of point2_t is: %lu\n", sizeof(point2_t));
  // As we can see the size is 16 and not 14 as expected, this because usually
  // compilers perform an optimization: data alignment. The compiler want to
  // improve data access speed so the uint16_t storage space is like a float
  // with 2 bytes not utilized but it results in faster access. We can directly
  // say not to store the struct this way with and attribute:
  // __attribute__((packed)) -> data alignment won't be performed

  // With the addition of attribute now the size is 14. This could be a
  // necessity in case we have limited ram space or something similar while
  // working on microcontrollers

  // Union
  // Declaration
  another_pt_t my_union;

  // Initializazion
  my_union.x = 300.0f;
  my_union.z = 100.5f;

  print_union_point(&my_union); // This the same value 3 times
  // The union takes the largest element of which it is composed and allocate a
  // memory space equal to that dimension, only one value per time can be stored
  // in that storage place, this is the reason why the printed values is 3 times
  // the last modified value

  printf("The size of my_union is: %lu\n", sizeof(my_union));
  printf("The size of my_union_ptr is: %lu\n", sizeof(&my_union));

  // Simple example use case: let's print the content of our string with HEX
  // numbers:
  print_array(my_union.str, sizeof(my_union));
  // A useful thing we can do with union is to code and encode data, by defining
  // the union as we did: with a numerical value and a string we can print the
  // numerical value as a number or as a string or hexadecimal value by calling
  // the string since it is stored at the same address location.
  // In an online hex to float converter we have to consider the endians, there
  // are little and big endians: big are called network byte order (ordered from
  // MSB to LSB), little endians is the opposite (from LSB to MSB)

  return 0;
}

// Function definition
void print_point(point_t *a) {
  printf("(%.3f, %.3f, %.3f)\n", a->x, a->y, a->z);
}

void print_union_point(another_pt_t *a) {
  printf("(%.3f, %.3f, %.3f)\n", a->x, a->y, a->z);
}

void print_array(unsigned char const *str, int len) {
  for (int i = 0; i < len; i++) {
    printf("%02X:", str[i]);
  }
  printf("\b (num. of bytes: %d)\n", len);
}