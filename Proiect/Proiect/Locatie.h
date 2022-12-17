#pragma once
#include <iostream>
using namespace std;

class Locatie {
private:
	const string denumire;
	const int nrMaximLocuri;
	int nrZone;
	string* zone;
	int* nrLocuriZona;

public:
	Locatie();
	Locatie(string denumire, int nrMaximLocuri, int nrZone, string* zone, int* nrLocuriZona);
	Locatie(const Locatie& l);
	~Locatie();

	
	string getDenumire();
	int getnrMaximLocuri();
	int getNrZone();
	string* getZone();
	int* getNrLocuriZona();

	void setDetaliiZone(int nrZone, string* zone, int* nrLocuriZona);

	void prelucrareZone(istream& in, int nr);
	void prelucrareNrLocuriZona(istream& in, int nr);
	bool isValid();
	int nrLocuriRepartizate(int nrZone,int* nrLocuriZona);
	static Locatie ceaMaiMareLocatie(Locatie* locatii, int nrLocatii);

	Locatie& operator=(const Locatie& l);
	string& operator[](int index);
	bool operator==(Locatie l);
	friend istream& operator>>(istream& in, Locatie& l);
	friend ostream& operator<<(ostream& out, Locatie l);
};