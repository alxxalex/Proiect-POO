#include <iostream>
#include <string>
#include "Locatie.h"
#include "Utils.h"
using namespace std;

	Locatie** Locatie::locatii = new Locatie*[100];
	
	int Locatie::nrLocatii = 0;

	Locatie :: Locatie() : denumire(""),nrMaximLocuri(0) {
		nrZone = 0;
		zone = nullptr;
		nrLocuriZona = nullptr;
	}

	//sunt permise locatii in care numarul de locuri repartizate este mai mic decat cel maxim
	Locatie::Locatie(string denumire, int nrMaximLocuri,int nrZone,string* zone,int* nrLocuriZona) 
		: denumire(denumire),nrMaximLocuri(nrMaximLocuri) {
		if (nrZone > 0 && zone != nullptr && nrLocuriZona != nullptr 
			&& nrLocuriRepartizate(nrZone,nrLocuriZona) < nrMaximLocuri) {
			this->nrZone = nrZone;
			this->zone = new string[nrZone];
			this->nrLocuriZona = new int[nrZone];
			for (int i = 0; i < nrZone; i++)
			{	
				if (Utils::isNumber(to_string(nrLocuriZona[i]))) {
					this->zone[i] = zone[i];
					this->nrLocuriZona[i] = nrLocuriZona[i];
				}
				else {
					throw exception("Date invalide pentru locatia respectiva");
				}
			}
		}
		else {
			throw exception("Date invalide pentru locatia respectiva");
		}
		
		locatii[nrLocatii] = new Locatie(*this);
		nrLocatii++;
	}

	Locatie::Locatie(const Locatie& l) : denumire(l.denumire), nrMaximLocuri(l.nrMaximLocuri) {
		nrZone = l.nrZone;
		zone = new string[nrZone];
		nrLocuriZona = new int[nrZone];
		for (int i = 0; i < nrZone; i++)
		{
			zone[i] = l.zone[i];
			nrLocuriZona[i] = l.nrLocuriZona[i];
		}
	}

	Locatie ::~Locatie() {
		if (this->zone != nullptr) {
			delete[] this->zone;
			this->zone = nullptr;
		}
		if (this->nrLocuriZona != nullptr) {
			delete[] this->nrLocuriZona;
			this->nrLocuriZona = nullptr;
		}
	}


	string Locatie::getDenumire() {
		return denumire;
	}

	int Locatie::getnrMaximLocuri() {
		return nrMaximLocuri;
	}

	int Locatie::getNrZone() {
		return nrZone;
	}

	string* Locatie::getZone() {
		if (zone != nullptr && nrZone > 0) {
			string* copy = new string[nrZone];
			for (int i = 0; i < nrZone; i++)
			{
				copy[i] = zone[i];
			}
			return copy;
		}
		return nullptr;
	}

	int* Locatie::getNrLocuriZona() {
		if (nrLocuriZona != nullptr && nrZone > 0) {
			int* copy = new int[nrZone];
			for (int i = 0; i < nrZone; i++)
			{
				copy[i] = nrLocuriZona[i];
			}
			return copy;
		}
		return nullptr;
	}

	Locatie** Locatie::getLocatii()
	{
		return locatii;
	}

	int Locatie::getNrLocatii()
	{
		return nrLocatii;
	}

	void Locatie::setDetaliiZone(int nrZone,string* zone,int* nrLocuriZona) {
		int suma = 0;
		for (int i = 0; i < nrZone; i++)
		{
			suma += nrLocuriZona[i];
		}
		if (nrZone > 0 && zone != nullptr && nrLocuriZona != nullptr && suma < nrMaximLocuri) {
			if (this->zone != nullptr) {
				delete[] this->zone;
			}
			if (this->nrLocuriZona != nullptr) {
				delete[] this->nrLocuriZona;
			}
			this->nrZone = nrZone;
			this->zone = new string[nrZone];
			this->nrLocuriZona = new int[nrZone];
			for (int i = 0; i < nrZone; i++)
			{
				this->zone[i] = zone[i];
				this->nrLocuriZona[i] = nrLocuriZona[i];
			}
		}
		else {
			cout << "Nu s-au putut seta zonele" << endl;
		}
	}

	void Locatie::prelucrareZone(istream& in,int nr) {
		string zona;
		zone = new string[nr];
		for (int i = 0; i < nr; i++)
		{
			cout << "Zona " << i + 1 << ": ";
			getline(in, zona);
			if (zona == "") {
				i--;
				cout << "Zona introdusa invalida!" << endl;
			}
			else { 
				zone[i] = zona;
			}
		}
	};

	void Locatie::prelucrareNrLocuriZona(istream& in,int nr) {
		string nrLocuri;
		nrLocuriZona = new int[nr];
		int suma = 0;
		for (int i = 0; i < nr; i++)
		{
			cout << "Numarul de locuri pentru zona " << i + 1 << ": ";
			in >> nrLocuri;
			in.ignore();
			if (!(Utils::isNumber(nrLocuri)) || stoi(nrLocuri) <= 0) {
				i--;
				cout << "Numar invalid de locuri in zona! " << endl;
			}
			else {
				if ((suma + stoi(nrLocuri)) <= nrMaximLocuri) {
					nrLocuriZona[i] = stoi(nrLocuri);
					suma += stoi(nrLocuri);
				}
				else {
					i--;
					cout << "Numarul de locuri introdus depaseste numarul maxim de locuri: " << nrMaximLocuri << endl;
				}
			}
		}
	}

	bool Locatie::isValid() {
		if (denumire == "" || nrMaximLocuri == 0 || nrZone == 0) {
			return false;
		}
		return true;
	}

	//suma locurilor introduse de la tastatura
	int Locatie::nrLocuriRepartizate(int nrZone,int* nrlocuriZona) {
		if (nrlocuriZona != nullptr) {
			int sum = 0;
			for (int i = 0; i < nrZone; i++)
			{
				sum += nrlocuriZona[i];
			}
			return sum;
		}
		else {
			cout << "Nu exista locuri in aceste zone" << endl;
		}
	};

	 Locatie Locatie::ceaMaiMareLocatie(Locatie** locatii,int nrLocatii) {
		 int max = 0,index = 0;

		 for (int i = 0; i < nrLocatii; i++)
		 {
			 if (locatii[i]->nrMaximLocuri > max) {
				 max = locatii[i]->nrMaximLocuri;
				 index = i;
			 }
		 }
		 return *locatii[index];
	}
	

	 Locatie& Locatie ::operator=(const Locatie& l) {
		 int suma = 0;
		 for (int i = 0; i < l.nrZone; i++)
		 {
			 suma += l.nrLocuriZona[i];
		 }
		 if (suma <= nrMaximLocuri) {
			 if (this->zone != nullptr) {
				 delete[] zone;
				 zone = nullptr;
			 }
			 if (this->nrLocuriZona != nullptr) {
				 delete[] nrLocuriZona;
				 nrLocuriZona = nullptr;
			 }
			 nrZone = l.nrZone;
			 zone = new string[nrZone];
			 nrLocuriZona = new int[nrZone];
			 for (int i = 0; i < nrZone; i++)
			 {
				 zone[i] = l.zone[i];
				 nrLocuriZona[i] = l.nrLocuriZona[i];
			 }
		 }
		 else {
			 cout << "Nu se poate realiza atribuirea" << endl;
		 }
		 return *this;

	 }

	 string& Locatie::operator[](int index) {
		 if (index >= 0 && index < nrZone) {
			 return zone[index];
		 }
		 else {
			 throw  exception("Index invalid");
		 }

	 }

	 bool Locatie::operator==(Locatie l) {
		 if (nrMaximLocuri == l.nrMaximLocuri && denumire == l.denumire) {
			 return true;
		 }
		 return false;
	 }

istream& operator>>(istream& in, Locatie& l) {
	int  nrZone;
	
	
	cout << "Numarul de zone: ";
	in >> nrZone;
	in.ignore();
	if (nrZone > 0) {
		l.nrZone = nrZone;

		if (l.zone != nullptr) {
			delete[] l.zone;
			l.zone = nullptr;
		}
		if (l.nrLocuriZona != nullptr) {
			delete[] l.nrLocuriZona;
			l.nrLocuriZona = nullptr;
		}
		
		l.prelucrareZone(in,nrZone);

		cout << endl;
		
		l.prelucrareNrLocuriZona(in,nrZone);

	}
	else {
		cout << "Numar invalid de zone" << endl;
	}

	return in;
}

ostream& operator<<(ostream& out, Locatie l) {
	out << "Denumirea locatiei este: " << l.denumire << endl;
	out << "Numarul maxim de locuri este: " << l.nrMaximLocuri << endl;
	out << "Numarul de zone este: " << l.nrZone << endl;
	out << "Zonele si numarul de locuri respectiv sunt: " << endl;
	for (int i = 0; i < l.nrZone; i++)
	{
		out << l.zone[i] << " care are " << l.nrLocuriZona[i] << " locuri" << endl;
	}
	
	return out;
}