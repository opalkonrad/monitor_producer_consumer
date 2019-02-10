#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "myMonitor.h"

extern int progDuration;

void MyMonitor::add(int id)
{
  buff.elems[buff.last] = id;
  buff.last = (buff.last + 1) % TABSIZE;
  ++buff.length;
}

int MyMonitor::get()
{
  if (buff.isRead == 1)
  {
    std::cout << "eats " << std::setw(8) << buff.elems[buff.first];

    int tmp = buff.elems[buff.first];
    buff.first = (buff.first + 1) % TABSIZE;
    --buff.length;
    buff.isRead = 0;
    return tmp;
  }

  std::cout << "tries " << std::setw(7) << buff.elems[buff.first];

  buff.isRead = 1;
  return -1;
}

void MyMonitor::print()
{
  int tmp = buff.first;

  std::cout << std::setw(12) << buff.length << " element(s): ";

  for (int i = 0; i < buff.length; ++i, ++tmp)
  {
    std::cout << buff.elems[tmp % TABSIZE] << " ";
  }

  std::cout << "\n";
}

MyMonitor::MyMonitor()
{
  buff.length = 0;
  buff.first = 0;
  buff.last = 0;
  buff.isRead = 0;
}

void MyMonitor::producer()
{
  int i = 0;

  while (1)
  {
    sleep(rand() % 2);
    enter();

    if (buff.length == TABSIZE)
    {
      wait(full);
    }

    std::cout << "P   adds" << std::setw(9) << i;
    add(i++);

    print();

    if (buff.length != 0)
    {
      signal(empty);
    }

    leave();
  }
}

void MyMonitor::consumer(int id)
{
  if (id == 1 || id == 3)
  { // consumer 1 and 3
    while (1)
    {
      sleep(rand() % 4);

      monitor_ac.enter();
      enter();

      if (buff.length == 0)
      {
        wait(empty);
      }

      std::cout << "C" << id << "  ";

      if (get() != -1)
      { // delete
        print();
        monitor_ac.leave();

        if (buff.length == TABSIZE - 1)
        {
          signal(full);
        }

        signal(read);

        leave();
      }
      else
      { // read
        print();
        wait(read);
        monitor_ac.leave();
        leave();
      }
    }
  }

  if (id == 2)
  { // consumer 2
    while (1)
    {
      sleep(rand() % 3);
      enter();

      if (buff.length == 0)
      {
        wait(empty);
      }

      std::cout << "C" << id << "  ";

      if (get() != -1)
      { // delete

        print();

        if (buff.length == TABSIZE - 1)
        {
          signal(full);
        }

        signal(read);

        leave();
      }
      else
      { // read
        print();
        wait(read);
        leave();
      }
    }
  }
}
