#include "monitor.h"

#define TABSIZE 10

struct Elements
{
  int elems[TABSIZE];
  bool isRead;
  int length, first, last;
};

class MonitorAC : public Monitor
{
};

class MyMonitor : private Monitor
{
private:
  MonitorAC monitor_ac;
  Elements buff;
  Condition empty, full, read;

  void add(int id);
  int get();
  void print();

public:
  MyMonitor();
  void producer();
  void consumer(int id);
};