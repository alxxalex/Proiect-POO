#pragma once
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
	static Bilet** bilete;
	
public:
	Bilet();
	Bilet(string tipBilet, int loc,Eveniment& e);
	Bilet(const Bilet& b);

	int getPret();
	string getTipBilet();
	long getId();
	int getLoc();
	bool getValidat();
	Eveniment getEveniment();
	static int getNrBilete();
	static Bilet** getBilete();

	void setTipBilet(string tip);
	void setLoc(int loc);
	void setEveniment(Eveniment e);

	void seteazaPret(string tipBilet);
	void valideaza();
	bool virtual esteTipBiletValid(string tipBilet,Eveniment e);
	bool locDisponibil(int loc, string tipBilet, Eveniment& e);
	bool virtual esteLocValid(int loc,string tipBilet,Eveniment& e);
	long creazaId();

	bool operator!();
	bool operator>(Bilet b1);
	bool operator<(Bilet b1);
	friend istream& operator>>(istream& in, Bilet& l);
	friend ostream& operator<<(ostream& out, Bilet l);
};