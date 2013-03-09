#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include <iostream>
#include "PRNG.h"
#include "printer.h"
#include "watcard.h"
#include "nameserver.h"
class VendingMachine { 

 protected:
  Printer* p;
  unsigned int vid;
  unsigned int costOfSoda;
  unsigned int* maxStockOfFlavour;
  NameServer* nameserver;
 public:
  enum Flavours { BluesBlackCherry, ClassicalCreamSoda, RockRootBeer, JazzLime };
  enum Status { BUY, STOCK, FUNDS }; 
  VendingMachine( Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
  virtual ~VendingMachine(); 
  virtual Status buy( Flavours flavour, WATCard*& card ); 
  virtual unsigned int* inventory();
  virtual void restocked();
  virtual unsigned int cost();
  virtual unsigned int getId();
};

class VendingMachineCardEater : public VendingMachine { 
 public:
  VendingMachineCardEater( Printer& prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
  Status buy( Flavours flavour, WATCard*& card);

};

class VendingMachineOverCharger : public VendingMachine { 
 public:
  VendingMachineOverCharger( Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
  Status buy( Flavours flavour, WATCard*& card);

};

#endif
