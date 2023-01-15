#pragma once
#include <iostream>
#include "Locatie.h"
using namespace std;

class Eveniment {
private:
	char* denumire;
	string data;
	string ora;
	Locatie* l;
	int* locuriOcupateZona;//vector pentru a verifica cate locuri mai sunt in fiecare zona
	int* locuriOcupateTotal;// vector pentru a verifica daca doua bilete sunt pe acelasi loc
	int* preturi;
	static Eveniment** evenimente;
	static int nrEvenimente ;
public:
	Eveniment();
	Eveniment(string data, string ora,const char* denumire,Locatie locatie,int* preturi);
	Eveniment(const Eveniment& e);
	~Eveniment();

	char* getDenumire();
	string getData();
	string getOra();
	Locatie getLocatie();
	int* getLocuriOcupateZona();
	int* getLocuriOcupateTotal();
	int* getPreturi();
	static Eveniment** getEvenimente();
	static int getNrEvenimente();

	void setDenumire(const char* denumire);
	void setData(string data);
	void setOra(string ora);
	void setLocatie(Locatie locatie);
	void setPreturi(int* preturi, int nrPreturi);

	bool hasValidPrices(Locatie locatie, int* preturi);
	void prelucrarePreturi(istream& in);
	bool hasValidData();
	bool virtual esteEvenimentInViitor();
	bool virtual esteEvenimentValid();

	Eveniment& operator=(const Eveniment& e);
	Eveniment& operator++();
	Eveniment& operator++(int a);
	explicit operator string();
	friend ostream& operator<<(ostream& out, Eveniment e);
	friend istream& operator>>(istream& in, Eveniment& e);
};
