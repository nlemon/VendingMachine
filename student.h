#ifndef __STUDENT_H__
#define __STUDENT_H__

#include<iostream>
#include"printer.h"
#include "watcardoffice.h"
#include "watcard.h"
#include "vendingmachine.h"
#include "nameserver.h"


class Student {
 
  Printer* printer;
  NameServer* nameserver;
  unsigned int studId;
  unsigned int favFlavour;
  unsigned int noOfPurchase;
  WATCardOffice* officeCard;
  WATCard* card;
  VendingMachine* vendy;
 public:
  Student(Printer&, NameServer&, WATCardOffice&, unsigned int, unsigned int);
  bool action();
  ~Student();
};


#endif
