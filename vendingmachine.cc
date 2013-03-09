#include "vendingmachine.h"
extern PRNG prng;
//VendingMachine constructor initializes the printer, nameServer and assigns the value of id, sodacost and maxstockperflavour
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour){
  p=&prt;
  vid=id;
  nameserver=&nameServer;
  costOfSoda=sodaCost;
  p->print( Printer::Vending, vid, 'S', costOfSoda);
  nameServer.VMregister(this);//register a new VendingMachine through the name server
  maxStockOfFlavour=new unsigned int[4]; 
  for(int i=0;i<4;i++){
  maxStockOfFlavour[i]=0;
  }
 
}
//buy() method takes flavour and card as input and returns STOCK if vendingmachine is out of stock, FUNDS if the card has insufficient balance
//and BUY if the student buys
VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard*& card){
  
  if(maxStockOfFlavour[flavour]==0){//If the VendngMachine is out of stock
    return STOCK;
  }

  else if(card->getBalance() < costOfSoda){//If the card balance is less than cost of soda
    return FUNDS;
  }

  else{
    int temp;
    temp=(card->getBalance())-costOfSoda;//reduce the card balance by the cost of soda
    card->assignBalance(temp);
  
    maxStockOfFlavour[flavour]--;//reduce the stock by 1
    p->print(Printer::Vending, vid, 'B', flavour, maxStockOfFlavour[flavour]);
    return BUY;
  }

}
//Inventory() methode returns the array of stock in the vending machine
unsigned int* VendingMachine::inventory(){
  p->print(Printer::Vending, vid, 'r');
  return maxStockOfFlavour;
}
//restocked is called after the vending machine is stocked to indicate transfer from truck is complete
void VendingMachine::restocked(){
  p->print( Printer::Vending, vid, 'R');
}
//returns the cost of soda
unsigned int VendingMachine::cost(){
  return costOfSoda;
}
//returns the Id of VendingMachine
unsigned int VendingMachine::getId(){
  return vid;
}
//VendingMachine destructor
VendingMachine::~VendingMachine(){
  p->print( Printer::Vending, vid, 'F');
  delete []maxStockOfFlavour;
}
//Derived class VendingMachineCardEater destroys the card 1 in 10 chances by deleting it and setting it to null
//VendingMachineCardEater Constructor is used to assign values to the Parent Class attributs such as id, sodacost, maxstockPerFlavour
VendingMachineCardEater::VendingMachineCardEater( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour): VendingMachine( prt, nameServer, id, sodaCost, maxStockPerFlavour){
 
}

//buy() method of VendingMachineCardEater calls the vendingmachine buy() method but 1 in 10 chances, it destroys the card 
VendingMachine::Status VendingMachineCardEater::buy(Flavours flavour, WATCard *&card){
  VendingMachine::Status tempstatus;
  tempstatus=VendingMachine::buy(flavour,card);
  int temp;
  temp=prng(9);
  if(temp==0){
    delete card;//1 in 10 chances of eating the card by deleting and setting it to null
    card=NULL;
  }
    return tempstatus;
}
//Derived class VendingMachineOverCharger is used to charge twice the cost of soda
//VendingMachineOverCharger constructor is used to assign the values to the parent vending machine such as id, 2*sodacost, macstockPerFlavour
VendingMachineOverCharger::VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour): VendingMachine(prt, nameServer, id, (2*sodaCost), maxStockPerFlavour){
  
}
//buy() method of the vendingmachineOverCharger calls the buy() method of the vendingmachine but with the sodacost=2*sodacost
VendingMachine::Status VendingMachineOverCharger::buy(Flavours flavour, WATCard*& card){
 VendingMachine::Status tempstatus=VendingMachine::buy(flavour, card);
 return tempstatus;
}

