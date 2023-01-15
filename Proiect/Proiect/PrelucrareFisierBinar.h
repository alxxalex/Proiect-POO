#pragma once
#include "PrelucrareFisier.h"
#include <list>

class PrelucrareFisierBinar : public PrelucrareFisier
{
public:
	static string numeFisier;
	static list<string>* fisierCitite;

	virtual void scriere( Bilet b) override;
	virtual void scriere( Eveniment e) override;
	virtual void scriere( Locatie l) override;
	virtual void citireBilet() override;
	virtual void citireEveniment() override;
	virtual void citireLocatie() override;
	void citire();
	void scriereFisiereCitite();
	void citireFisiereCitite();
	void scriereBileteEvenimente();
};

