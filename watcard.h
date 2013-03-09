#ifndef __WATCARD_H__
#define __WATCARD_H__

#include<iostream>

class WATCard{
  unsigned int balance;
 public:
  WATCard(unsigned int);
  void changeBalance(unsigned int);
  unsigned int getBalance();
  void assignBalance(unsigned int);
};

#endif

