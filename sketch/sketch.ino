#include <Arduino_Threads.h>

//ardiuno libs
#include <Wire.h>

//custom
#include "version.h"
#include "worker.h"

void dispHandler(void);

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  rtos::Thread* t = new rtos::Thread(osPriorityNormal, OS_STACK_SIZE, nullptr, "dispThrd");
  t->start(dispHandler);
}

void loop() {
  
}

void dispHandler(void) {
  Serial.begin(9600);
  while (!Serial) {}
  for (;;) {
    //touchscreen events
    // should be handled with interrupts instead - this is a processing routine.
    //100 ms sleep
    rtos::Thread::sleep_for(rtos::Kernel::Clock::duration_u32(100));
    //do something every 100ms
    Serial.println("Display Thread doing something");
  }
}