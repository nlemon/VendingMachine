#include "nameserver.h"
#include "vendingmachine.h"

/*The NameServer constructor; consumes a Printer reference, the number of vending machines, and the number of students (both as unsigned ints).*/

NameServer::NameServer(Printer& prt, unsigned int vendingMachines, unsigned int numOfStudents){
  printer = &prt;
  printer->print(Printer::NameServer, 'S');
  currentMachine = 0;
  totalMachines = vendingMachines;
  numOfStudent = numOfStudents;
  studentsInitialized = 0;
  machineList = new VendingMachine* [vendingMachines];
  students = new unsigned int[numOfStudents];
}

//VMregister consumes a VendingMachine pointer and returns void. The function adds the given VendingMachine to machineList.

void NameServer::VMregister(VendingMachine* vm){
  printer->print(Printer::NameServer, 'R', vm->getId());
  machineList[currentMachine] = vm;
  currentMachine += 1;
  return;
}

//getMachine consumes an unsigned int representing a student id and returns a p//ointer to the VendingMachine to which the student is associated.
 
VendingMachine* NameServer::getMachine(unsigned int ID){
  if(studentsInitialized < numOfStudent){//initial machines
    unsigned int initialIndex = ID % totalMachines;
    students[ID] = initialIndex;
    printer->print(Printer::NameServer, 'N', ID, machineList[initialIndex]->getId());
    studentsInitialized += 1;
    return machineList[initialIndex];
  }
  unsigned int newMachineIndex = (students[ID] + 1) % totalMachines;
  students[ID] = newMachineIndex;
  printer->print(Printer::NameServer, 'N', ID, machineList[newMachineIndex]->getId());
  return machineList[newMachineIndex];
}

//getMachineList consumes nothing and returns an array of pointers to VendingMa//chines. This function is used by the Truck for its delivery run.

VendingMachine** NameServer::getMachineList(){
  return machineList;
}

//NameServer destructor.

NameServer::~NameServer(){
  printer->print(Printer::NameServer, 'F');
  delete [] machineList;
  delete [] students;
}
