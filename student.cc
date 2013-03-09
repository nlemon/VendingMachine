#include "student.h"

extern PRNG prng;
//Student constructor to initialize printer, namesever, watcardoffice 
Student::Student(Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, unsigned int id, unsigned int maxPurchases){
	
	printer = &prt;
	studId=id;
	nameserver = &nameServer;
	noOfPurchase=prng(1,maxPurchases);//number of purchas is random number between 1 to maxPurchases
	favFlavour=prng(3);//favFlavour is a random number between 0 to 3
	printer->print(Printer::Student, studId, 'S', favFlavour, noOfPurchase);
	officeCard=&cardOffice;
        card=officeCard->create(studId, 5);//create a new card with $5 balance
	vendy=nameServer.getMachine(studId);//get a new machine from nameserver
	printer->print( Printer::Student, studId, 'V', vendy->getId());
}

//action() method checks for insufficienct funds, stock of favflavour, and buys from the vending machine and returns true
//action() returns false if student completes purchase
bool Student::action(){

	if(noOfPurchase==0)
		return false;
	else{
                VendingMachine::Status situation = vendy->buy((VendingMachine::Flavours)favFlavour, card);

		if(situation==VendingMachine::BUY){
                  if(!card){//checks if the card is destroyed
		    printer->print( Printer::Student, studId, 'D');
		    card=officeCard->create(studId,5);//if destroyed, student creates a new card with $5 balance
                  }
			printer->print( Printer::Student, studId, 'B', card->getBalance());
			noOfPurchase--;//after each buy, the number of purchase is decremented by 1 
			return true;
		}

		if(situation==VendingMachine::FUNDS){//if student has insufficient funds to buy soda
        
		if(!card){
                    printer->print( Printer::Student, studId, 'D');
                    card=officeCard->create(studId,5);
                    printer->print( Printer::Student, studId, 't', 3);//transfer $3 to the watcard
                    officeCard->transfer(studId, 3, *card);
		    printer->print( Printer::Student, studId, 'T', card->getBalance());             
                    return true;

  		}
		//transfer $3 to the watcard until the balance of watcard is greater than the cost of soda
			while(card->getBalance()<vendy->cost()){
                        printer->print( Printer::Student, studId, 't', 3);
			officeCard->transfer(studId, 3, *card);
			printer->print( Printer::Student, studId, 'T', card->getBalance());		
			}
		return true;
		}	
		
		//if the vending machine is out of stock of the students favFlavour
		if(situation==VendingMachine::STOCK){
		  if(!card){
		    printer->print( Printer::Student, studId, 'D');
		    card=officeCard->create(studId,5);
                  }
			vendy=nameserver->getMachine(studId);//student gets a new vendingmachine by calling the nameserver
			printer->print( Printer::Student, studId, 'V', vendy->getId());
			return true;
		}
			

	}
return true;
}
//student destructor	
Student::~Student(){
	printer->print(Printer::Student, studId, 'F');
	delete card;
	

}
