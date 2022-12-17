#include <iostream>
#include "Locatie.h"
#include "Eveniment.h"
using namespace std;

class Bilet {
private:
	string tipBilet;
	const long id;
	int loc;
	bool validat;
	Eveniment eveniment;
	int pret ;
	static int nrBilete;
	
public:
	Bilet();
	Bilet(string tipBilet, int loc,Eveniment& e);
	Bilet( Bilet& b);

	int getPret();
	string getTipBilet();
	long getId();
	int getLoc();
	bool getValidat();
	Eveniment getEveniment();

	void setTipBilet(string tip);
	void setLoc(int loc);
	void setEveniment(Eveniment e);

	void seteazaPret(string tipBilet);
	void valideaza();
	bool esteTipBiletValid(string tipBilet,Eveniment e);
	bool locDisponibil(int loc, string tipBilet, Eveniment& e);
	bool esteLocValid(int loc,string tipBilet,Eveniment& e);
	long creazaId();

	bool operator!();
	bool operator>(Bilet b1);
	bool operator<(Bilet b1);
	friend istream& operator>>(istream& in, Bilet& l);
	friend ostream& operator<<(ostream& out, Bilet l);
};