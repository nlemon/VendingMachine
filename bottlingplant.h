#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include <iostream>
#include "PRNG.h"
#include "printer.h"
class Truck;
class NameServer; 

class BottlingPlant{
  Printer* printer;
  unsigned int time;
  unsigned int maxShip;
  unsigned int* sodaStock;
  Truck* truck;
 public:
  BottlingPlant(Printer&, NameServer&, unsigned int, unsigned int, unsigned int , unsigned int);
  void getShipment(unsigned int*);
  void action();
  ~BottlingPlant();
};

#endif
