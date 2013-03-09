#include "watcardoffice.h"

extern PRNG prng;
//WATCardOffice constructor
WATCardOffice::WATCardOffice( Printer &prt){
	p=&prt;
	prt.print( Printer::WATCardOffice, 'S');
}
//create() method is used to create a card with $5 balance by calling the WATCard constructor and returns a watcard
WATCard* WATCardOffice::create( unsigned int id, unsigned int amount=5){
	WATCard* card=new WATCard(amount);
	p->print( Printer::WATCardOffice, 'C', id, amount);
	return card;

}
//transfer() method is used to transfer amount to the their watcard
void WATCardOffice::transfer( unsigned int id, unsigned int amount, WATCard &card){
	p->print( Printer::WATCardOffice, 't', id, amount );
	int rand=prng(3);//1 in 4 chances that only 1/2 of requested amount is deposited
	if(rand==0){
		amount/=2;
	}

	card.changeBalance(amount);
	p->print( Printer::WATCardOffice, 'T', id, amount );
}

//WATCardOffice destructor
WATCardOffice::~WATCardOffice(){
	p->print( Printer::WATCardOffice, 'F');
}
