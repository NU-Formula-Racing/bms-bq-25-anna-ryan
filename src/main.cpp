#include <Arduino.h>
#include "bms.hpp"

void setup() {
  bms_init();
}

void loop() {
  tick_bms();
}

