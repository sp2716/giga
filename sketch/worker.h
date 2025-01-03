#ifndef WORKER_H
#define WORKER_H
#include <Arduino_GigaDisplayTouch.h>
extern Arduino_GigaDisplayTouch * pTouchDetector;
void* worker(void* vargs);
#endif