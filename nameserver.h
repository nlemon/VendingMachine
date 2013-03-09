#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include<iostream>
#include<vector>
#include<algorithm>
#include"printer.h"
class VendingMachine;

class NameServer{
  Printer* printer;
  unsigned int currentMachine;
  unsigned int totalMachines;
  unsigned int numOfStudent;
  unsigned int studentsInitialized;

//machineList is an array of pointers to vending machines with order dependent on when they were registered.
  VendingMachine** machineList;

//students is an array which associates a student id (by index) with a vending machine (also by index). 
  unsigned int* students;
 public:
  NameServer(Printer&, unsigned int, unsigned int);
  void VMregister(VendingMachine*);
  VendingMachine* getMachine(unsigned int);
  VendingMachine** getMachineList();
  ~NameServer();
};

#endif
