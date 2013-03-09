#include"bottlingplant.h"

extern PRNG prng;
#include "truck.h"

//BottlingPlant constructor; consumes a Printer and NameServer reference, the n//umber of vending machines, maximum shipped bottles, maximum stock for a flavo//ur, and the time between shipments (all as unsigned ints). As part of the ini//tialization, the constructor generates bottles, creates a truck, and sends th//e truck on a delivery.
 
BottlingPlant::BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int vendingMachines, unsigned int maxShipped, unsigned int maxStock, unsigned int timeBetween){
  printer = &prt;
  printer->print(Printer::BottlingPlant, 'S');
  time = timeBetween;
  maxShip = maxShipped;
  sodaStock = new unsigned int[4];

  for(unsigned int i = 0; i < 4; i += 1){
    sodaStock[i] = prng(maxShip); 
  }

  int inventory = 0;
  for(int i = 0; i < 4; i += 1){
    inventory += sodaStock[i];
  }
 
  truck = new Truck(prt, nameServer, *this, vendingMachines, maxStock);
  printer->print(Printer::BottlingPlant, 'G', inventory);
  printer->print(Printer::BottlingPlant, 'P');
  truck->action();
}

//getShipment consumes an array of unsigned ints and returns void. The function//is used by the Truck to get its delivery order.

void BottlingPlant::getShipment(unsigned int* cargo){
  for(unsigned int i = 0; i < 4; i += 1){ 
    cargo[i] = sodaStock[i];
  }
  return;
}

//action consumes nothing and returns void. The function generates bottles for //a production run, then sends the truck off (if its there) on its delivery run

void BottlingPlant::action(){
  if(!prng(4)){
    printer->print(Printer::BottlingPlant, 'X'); return;
  }
  if(prng(time-1)) return;

  for(unsigned int i = 0; i < 4; i += 1){
    sodaStock[i] = prng(maxShip);
  }

  int inventory = 0;
  for(int i = 0; i < 4; i += 1){
    inventory += sodaStock[i];
  }

  printer->print(Printer::BottlingPlant, 'G', inventory);
  printer->print(Printer::BottlingPlant, 'P');
  truck->action();
  return;
}

//BottlingPlant destructor.

BottlingPlant::~BottlingPlant(){
  printer->print(Printer::BottlingPlant, 'F');
  delete [] sodaStock;
  delete truck;
}
