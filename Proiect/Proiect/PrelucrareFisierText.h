#pragma once
#include "PrelucrareFisier.h"

class PrelucrareFisierText :public PrelucrareFisier
{
private:
	string numeFisier;
public:
	virtual void scriere( Bilet b) override;
	virtual void scriere( Eveniment e) override;
	virtual void scriere( Locatie l) override;
	virtual void citireBilet() override;
	virtual void citireEveniment() override;
	virtual void citireLocatie() override;
	void citire(string numeFisier);
	bool valideazaFisier();
};

