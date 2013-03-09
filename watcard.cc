#include"watcard.h"

/*WATCard constructor; consumes an unsigned int representing a WATCard balance.*/

WATCard::WATCard(unsigned int bal = 0){
  balance = bal;
}

/*changeBalance consumes an unsigned int representing an amount to be added to the current balance of a WATCard and returns void.*/
void WATCard::changeBalance(unsigned int amount){
  balance+= amount;
  return;
}

/*getBalance consumes nothing and returns an unsigned int representing the current balance on a WATCard.*/
unsigned int WATCard::getBalance(){
  return balance;
}

/*assignBalance consumes an unsigned int representing an amount which will be set to be the new balance of a WATCard and returns void.*/
void WATCard::assignBalance(unsigned int amount){
  balance=amount;
}

