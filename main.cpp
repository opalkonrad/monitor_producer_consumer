#include <iostream>

#include "myMonitor.h"

MyMonitor my_monitor;
void* start(void* arg);
int progDuration;

int main(int argc, char* argv[]) {
  if(argc == 2) {
    progDuration = atoi(argv[1]);
  }
  else {
    progDuration = 30;
  }
  
  pthread_t producer, consumerA, consumerB, consumerC;

  int prod = 0;
  int consA = 1;
  int consB = 2;
  int consC = 3;

  pthread_create(&consumerA, NULL, start, &consA);
  pthread_create(&consumerB, NULL, start, &consB);
  pthread_create(&consumerC, NULL, start, &consC);
  pthread_create(&producer, NULL, start, &prod);

  sleep(progDuration);
  
  return 0;
}

void* start(void* arg) {
  auto* i = static_cast<int*> (arg);

  if(*i == 0) {
    my_monitor.producer();
  }
  
  my_monitor.consumer(*i);
}
