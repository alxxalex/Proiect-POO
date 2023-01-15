#pragma once
using namespace std;
#include <iostream>
#include <fstream>

#include "Bilet.h"

class PrelucrareFisier
{

public:
	virtual void scriere(Bilet b) = 0;
	virtual void scriere(Eveniment e) = 0;
	virtual void scriere(Locatie l) = 0;
	virtual void citireBilet() = 0;
	virtual void citireEveniment() = 0;
	virtual void citireLocatie() = 0;
};

