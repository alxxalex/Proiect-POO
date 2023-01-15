#include "PrelucrareFisierBinar.h"
#include "Meniu.h"

list<string>* PrelucrareFisierBinar::fisierCitite = new list<string>();
string PrelucrareFisierBinar::numeFisier = "";

void PrelucrareFisierBinar::scriere( Bilet b)
{
	ofstream f("bilete.bin", ios::out | ios::binary | ios::app);
	int length = b.getTipBilet().length();
	f.write((char*)&length, sizeof(length));
	f.write(b.getTipBilet().c_str(), length + 1);

	int loc = b.getLoc();
	f.write((char*)&loc, sizeof(loc));

	//Pt a verifica daca sete validat
	if (b.getValidat()) { // v e 0 mereu
		int v = 1;
		f.write((char*)&v, sizeof(v));
	}
	else {
		int v = 0;
		f.write((char*)&v, sizeof(v));
	}

	length = strlen(b.getEveniment().getDenumire());
	f.write((char*)&length, sizeof(length));

	f.write(b.getEveniment().getDenumire(), length + 1);

	f.close();

	int i;
	for ( i = 0; i < Eveniment::getNrEvenimente(); i++)
	{
		if (strcmp(Eveniment::getEvenimente()[i]->getDenumire(), b.getEveniment().getDenumire()) == 0) {
			break;
		}
	}

	if (i == Eveniment::getNrEvenimente()) {
		//scriere eveniment
		ofstream f1("evenimente.bin", ios::out | ios::binary | ios::app);
		int length1 = strlen(b.getEveniment().getDenumire());
		f1.write((char*)&length1, sizeof(length1));
		f1.write(b.getEveniment().getDenumire(), length1 + 1);

		length1 = b.getEveniment().getData().length();
		f1.write((char*)&length1, sizeof(length1));
		f1.write(b.getEveniment().getData().c_str(), length1 + 1);

		length1 = b.getEveniment().getOra().length();
		f1.write((char*)&length1, sizeof(length1));
		f1.write(b.getEveniment().getOra().c_str(), length1 + 1);

		length1 = b.getEveniment().getLocatie().getNrZone();
		f1.write((char*)&length1, sizeof(length1));
		for (int i = 0; i < length1; i++)
		{
			f1.write((char*)&b.getEveniment().getPreturi()[i], sizeof(b.getEveniment().getPreturi()[i]));
		}

		length1 = b.getEveniment().getLocatie().getDenumire().length();
		f1.write((char*)&length1, sizeof(length1));
		string denumireLocatie = b.getEveniment().getLocatie().getDenumire();
		f1.write(denumireLocatie.c_str(), length1 + 1);
		scriere(b.getEveniment().getLocatie());

		f1.close();
	}
}

void PrelucrareFisierBinar::scriere( Eveniment e)
{
	ofstream f("evenimente.bin", ios::out | ios::binary | ios::app);
	int length = strlen(e.getDenumire());
	f.write((char*)&length, sizeof(length));
	f.write(e.getDenumire(), length + 1);

	length = e.getData().length();
	f.write((char*)&length, sizeof(length));
	f.write(e.getData().c_str(), length + 1);

	length = e.getOra().length();
	f.write((char*)&length, sizeof(length));
	f.write(e.getOra().c_str(), length + 1);

	length = e.getLocatie().getNrZone();
	f.write((char*)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		f.write((char*)&e.getPreturi()[i], sizeof(e.getPreturi()[i]));
	}

	length = e.getLocatie().getDenumire().length();
	f.write((char*)&length, sizeof(length));
	string denumireLocatie = e.getLocatie().getDenumire();
	f.write(denumireLocatie.c_str(),length+1);
	int i;
	for ( i = 0; i < Locatie::getNrLocatii(); i++)
	{
		if (Locatie::getLocatii()[i]->getDenumire() == e.getLocatie().getDenumire()) {
			break;
		}
	}
	if (i == Locatie::getNrLocatii()) {
		scriere(e.getLocatie());
	}

	f.close();
}

void PrelucrareFisierBinar::scriere( Locatie l)
{
	ofstream f("locatii.bin", ios::out | ios::binary | ios::app);

	int length = l.getDenumire().length();
	f.write((char*)&length, sizeof(length));
	f.write(l.getDenumire().c_str(), length + 1);
	int nrMaxLocuri = l.getnrMaximLocuri();
	f.write((char*)&nrMaxLocuri, sizeof(nrMaxLocuri));
	int nrZone = l.getNrZone();
	f.write((char*)&nrZone, sizeof(nrZone));
	for (int i = 0; i < nrZone; i++)
	{
		string zona = l.getZone()[i];
		length = zona.length();
		f.write((char*)&length, sizeof(length));
		f.write(zona.c_str(), length + 1);
	}
	for (int i = 0; i < nrZone; i++)
	{
		int nrLocuri = l.getNrLocuriZona()[i];
		f.write((char*)&nrLocuri, sizeof(nrLocuri));
	}
	f.close();
}

void PrelucrareFisierBinar::citireBilet()
{
	ifstream f("bilete.bin", ios::in | ios::binary);
	int length = 0;
	while (f.read((char*)&length, sizeof(length))) {
		char* sir = new char[length + 1];
		f.read(sir, length + 1);
		string tipBilet = sir;
		delete[] sir;

		int loc = 0;
		f.read((char*)&loc, sizeof(loc));

		int v;
		f.read((char*)&v, sizeof(v));


		f.read((char*)&length, sizeof(length));
		char* denumireEveniment = new char[length + 1];
		f.read(denumireEveniment, length + 1);

		for (int i = 0; i < Eveniment::getNrEvenimente(); i++)
		{
			if (strcmp(Eveniment::getEvenimente()[i]->getDenumire(), denumireEveniment) == 0) {
				Bilet b(tipBilet, loc, (*Eveniment::getEvenimente()[i]));
				if (v == 1) {
					b.valideaza(); 
					Bilet::getBilete()[Bilet::getNrBilete() - 1]->valideaza();
				}
				Meniu::bileteDeSalvat->push_back(b);
			}
		}
	}
}

void PrelucrareFisierBinar::citireEveniment()
{
	ifstream f("evenimente.bin", ios::in | ios::binary);
	int length = 0;
	while (f.read((char*)&length, sizeof(length))) {
		
		char* denumire = new char[length + 1];
		f.read(denumire, length + 1);

		f.read((char*)&length, sizeof(length));
		char* sir = new char[length + 1];
		f.read(sir, length + 1);
		string data = sir;
		delete[] sir;

		f.read((char*)&length, sizeof(length));
		sir = new char[length + 1];
		f.read(sir, length + 1);
		string ora = sir;
		delete[] sir;

		f.read((char*)&length, sizeof(length));
		int* preturi = new int[length];
		for (int i = 0; i < length; i++)
		{
			f.read((char*)&preturi[i], sizeof(preturi[i]));
		}

		f.read((char*)&length, sizeof(length));
		sir = new char[length + 1];
		f.read(sir, length + 1);
		string denumireLocatiei = sir;
		delete[] sir;

		for (int i = 0; i < Locatie::getNrLocatii(); i++)
		{
			if (Locatie::getLocatii()[i]->getDenumire() == denumireLocatiei) {
				Eveniment e(data, ora, denumire, (*Locatie::getLocatii()[i]), preturi);
				Meniu::evenimenteDeSalvat->push_back(e);
			}
		}
		
	}
	f.close();
}

void PrelucrareFisierBinar::citireLocatie()
{
	ifstream f("locatii.bin", ios::in | ios::binary);
	int length = 0;
	while (f.read((char*)&length, sizeof(length))) {

		char* sir = new char[length + 1];
		f.read(sir, length + 1);
		string denumire = sir;
		delete[] sir;

		int nrMaxLocuri = 0;
		f.read((char*)&nrMaxLocuri, sizeof(nrMaxLocuri));

		int nrZone = 0;
		f.read((char*)&nrZone, sizeof(nrZone));

		string* zone = new string[nrZone];
		int* nrLocuriZona = new int[nrZone];
		for (int i = 0; i < nrZone; i++)
		{
			f.read((char*)&length, sizeof(length));
			char* sir = new char[length + 1];
			f.read(sir, length + 1);
			zone[i] = sir;
			delete[] sir;
		}

		for (int i = 0; i < nrZone; i++)
		{
			f.read((char*)&nrLocuriZona[i], sizeof(nrLocuriZona[i]));
		}

		Locatie l(denumire, nrMaxLocuri, nrZone, zone, nrLocuriZona);
	}

	f.close();
}

void PrelucrareFisierBinar::citire() {
	citireLocatie();
	citireEveniment();
	citireBilet();
	citireFisiereCitite();
}

void PrelucrareFisierBinar::scriereFisiereCitite()
{
	ofstream f("fisiereCitite.bin", ios::out | ios::binary | ios::app);
	int length = numeFisier.length();
	f.write((char*)&length, sizeof(length));
	f.write(numeFisier.c_str(), length + 1);
}

void PrelucrareFisierBinar::citireFisiereCitite()
{
	ifstream f("fisiereCitite.bin", ios::in | ios::binary);
	int length = 0;
	while (f.read((char*)&length, sizeof(length))) {
		char* sir = new char[length + 1];
		f.read(sir, length + 1);
		string nume = sir;
		delete[] sir;

		fisierCitite->push_back(nume);
	}
}

void PrelucrareFisierBinar::scriereBileteEvenimente() {

	ofstream f("evenimente.bin", ios::out | ios::binary | ios::trunc);
	for (int i = 0; i < Meniu::evenimenteDeSalvat->size(); i++)
	{
		scriere(Meniu::evenimenteDeSalvat->at(i));
	}
	ofstream f1("bilete.bin", ios::out | ios::binary | ios::trunc);
	for (int i = 0; i < Meniu::bileteDeSalvat->size(); i++)
	{
		scriere(Meniu::bileteDeSalvat->at(i));
	}
}
