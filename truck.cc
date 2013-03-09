#include"truck.h"

//Truck constructor; consumes a Printer, NameServer, and BottlingPlant referenc//e, the number of vending machines, and the maximum stock per flavour (both as//unsigned ints).
 
Truck::Truck(Printer& prt, NameServer& nameServer, BottlingPlant& plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour){
  printer = &prt;
  server = &nameServer;
  numberOfVendingMachines = numVendingMachines;
  bossMan = &plant;
  maxStock = maxStockPerFlavour;
  product = new unsigned int[4];
  printer->print(Printer::Truck, 'S'); 
}

//action consumes nothing and returns void. The function goes to each registere//d VendingMachine and attempts to fill it.

void Truck::action(){
  bossMan->getShipment(product);
  shipmentSize = 0;

  for(unsigned int i = 0; i < 4; i += 1){
    shipmentSize += product[i];
  }
  printer->print(Printer::Truck, 'P', shipmentSize);
  if(!shipmentSize) return;
  VendingMachine** machines = server->getMachineList();

  for(unsigned int i = 0; i < numberOfVendingMachines; i += 1){
    VendingMachine* current = machines[i];
    unsigned int* stock = current->inventory();
    printer->print(Printer::Truck, 'd', current->getId(), shipmentSize);
    unsigned int unsuccessful = 0;
    unsigned int unreplenished = 0;

    for(unsigned int j = 0; j < 4; j += 1){//fill current machine
      unsigned int bottlesNeeded = maxStock - stock[j];
      if(product[j] >= bottlesNeeded){//truck has enough bottles to fill
        stock[j] = maxStock;
        product[j] -= bottlesNeeded;
        shipmentSize -= bottlesNeeded; continue;
      }
      else{//truck does not have enough bottles to fill
        shipmentSize -= product[j];
        unreplenished += (bottlesNeeded - product[j]);
        stock[j] += product[j];
        product[j] = 0;
        unsuccessful = 1; continue;
      }
    }//end for
  
    if(unsuccessful == 1){//did not completely fill
      printer->print(Printer::Truck, 'U', current->getId(), unreplenished);
      unsuccessful = 0; 
      unreplenished = 0;
    }
    printer->print(Printer::Truck, 'D', current->getId(), shipmentSize);
    current->restocked();
    if(!shipmentSize) break;
    continue;
  }//end for

  return;
}

//Truck destructor.

Truck::~Truck(){
  printer->print(Printer::Truck, 'F');
  delete [] product;
}
