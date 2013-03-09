#ifndef __TRUCK_H__
#define __TRUCK_H__

#include <iostream>
#include "printer.h"
#include "bottlingplant.h"
#include "nameserver.h"
#include "vendingmachine.h"

class Truck{
  unsigned int maxStock;
  unsigned int numberOfVendingMachines;
  unsigned int shipmentSize;
  unsigned int* product;
  BottlingPlant* bossMan;
  Printer* printer;
  NameServer* server;
 public:
  Truck(Printer&, NameServer&, BottlingPlant&, unsigned int, unsigned int);
  void action();
  ~Truck();
};

#endif
