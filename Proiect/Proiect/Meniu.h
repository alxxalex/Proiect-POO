#pragma once
#include<iostream>
#include "Bilet.h"
#include <vector>
using namespace std;

class Meniu
{
public:
	static vector<Eveniment>* evenimenteDeSalvat;
	static vector<Bilet>* bileteDeSalvat;

	Meniu();
	void citire();
	void scriere();
	string* prelucrareZone(int nr);
	int* prelucrareNrLocuriZona(int nr,int nrMaximLocuri);
	int* prelucrarePreturi(string* zone, int nrZone);
	void prelucrareDateEveniment(string& denumire, string& data, string& ora);
	void salvareFisier(Eveniment e);
	void prelucrareDateBilet(Eveniment e);
	void cautareDupaNume(string nume,string tip);
	static void salvare();
};

