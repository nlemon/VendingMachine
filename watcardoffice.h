#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include<iostream>
#include "printer.h"
#include "watcard.h"
#include "PRNG.h"

class WATCardOffice{

  Printer* p;
 public:
  WATCardOffice(Printer& prt);
  WATCard* create(unsigned int id, unsigned int amount);
  void transfer(unsigned int id, unsigned int amount, WATCard& card);
  ~WATCardOffice();
};
#endif
