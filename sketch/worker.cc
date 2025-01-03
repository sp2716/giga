#include "worker.h"
//Handles touch screen events
void* worker(void* vargs) {
  pTouchDetector->begin();
  while(1){
    //process touchscreen inputs here
    ;
  }
  pTouchDetector->end();
  return NULL;
}