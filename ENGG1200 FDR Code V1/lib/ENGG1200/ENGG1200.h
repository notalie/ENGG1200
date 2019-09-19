#include <SPI.h>
#include "RF24.h"

// This is here so you can see how the data is packaged
#define grav_const_fact 0.00059875488
#define mod_offset 1670.13252568
typedef struct Package {
  int16_t x;
  int16_t y;
  int16_t z;
  int16_t gx;
  int16_t gy;
  int16_t gz;
  int16_t timeVal;
}Package; // Refer to this as a Package in your code


int transmit(Package);
int transmit_code(char*);
void setup_radio(void);
void prep_data(Package*, int16_t, int16_t, int16_t, int16_t, int16_t, int16_t, int16_t);
