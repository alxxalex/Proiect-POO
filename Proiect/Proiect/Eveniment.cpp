#include <iostream>
#include <string>
#include "Eveniment.h"
#include "Utils.h"

using namespace std;

int Eveniment::nrEvenimente = 0;

	Eveniment::Eveniment() {
		denumire = nullptr;
		data = "";
		ora = "";
		l = nullptr;
		locuriOcupateZona = nullptr;
		locuriOcupateTotal = nullptr;
		preturi = nullptr;

		nrEvenimente++;
	}

	Eveniment::Eveniment(string data, string ora ,const char* denumire,Locatie locatie,int* preturi) {
			if (locatie.isValid() && Utils::isValidDate(data) 
				&& Utils::isValidHour(ora) && Utils::hasOnlyLetters(denumire) && hasValidPrices(locatie,preturi)) {
				l = new Locatie(locatie);
				this->data = data;
				this->ora = ora;
				this->denumire = new char[strlen(denumire) + 1];
				strcpy_s(this->denumire, strlen(denumire) + 1, denumire);

				locuriOcupateZona = new int[locatie.getNrZone()+1];
				for (int i = 0; i < locatie.getNrZone(); i++)
				{
					locuriOcupateZona[i] = 0;
				}
				locuriOcupateTotal = new int[locatie.nrLocuriRepartizate(locatie.getNrZone(),locatie.getNrLocuriZona() ) + 1];
				this->preturi = new int[locatie.getNrZone() + 1];
				for (int i = 0; i < locatie.getNrZone(); i++)
				{
					this->preturi[i] = preturi[i];
				}

				nrEvenimente++;
			}
			else {
				throw exception("Date invalide pentru evenimentul respectiv");
			}
		
	}

	Eveniment::Eveniment(Eveniment& e)
	{
		if (e.esteEvenimentValid()) {

				
			l = new Locatie(*e.l);
			data = e.data;
			ora = e.ora;
			denumire = new char[strlen(e.denumire) + 1];
			strcpy_s(denumire, strlen(e.denumire) + 1, e.denumire);

			locuriOcupateZona = new int[l->getNrZone()+1];
			for (int i = 0; i < l->getNrZone(); i++)
			{
				locuriOcupateZona[i] = e.locuriOcupateZona[i];
			}

			locuriOcupateTotal = new int[l->nrLocuriRepartizate(l->getNrZone(), l->getNrLocuriZona()) + 1];
			for (int i = 0; i < l->nrLocuriRepartizate(l->getNrZone(), l->getNrLocuriZona()); i++)
			{
				locuriOcupateTotal[i] = e.locuriOcupateTotal[i];
			}

			preturi = new int[l->getNrZone() + 1];
			for (int i = 0; i < l->getNrZone(); i++)
			{
				preturi[i] = e.preturi[i];
			}

		}
	}

	Eveniment::~Eveniment()
	{
		if (denumire != nullptr) {
			delete[] denumire;
			denumire = nullptr;
		}
		if (l != nullptr) {
			delete l;
			l = nullptr;
		}
		if (locuriOcupateZona != nullptr) {
			delete[] locuriOcupateZona;
			locuriOcupateZona = nullptr;
		}
		if (locuriOcupateTotal != nullptr) {
			delete[] locuriOcupateTotal;
			locuriOcupateTotal = nullptr;
		}
		if (preturi != nullptr) {
			delete[] preturi;
			preturi = nullptr;
		}
	}

	char* Eveniment::getDenumire() {
		if (denumire) { 
			return denumire;
		}
	};

	string Eveniment::getData() {
		return data;
	};

	string Eveniment::getOra() {
		return ora;
	};

	Locatie Eveniment::getLocatie() {
		if (l != nullptr) {
			return *l;
		}
	};

	int* Eveniment::getLocuriOcupateZona() {
		if (locuriOcupateZona != nullptr) {
			return locuriOcupateZona;
		}
	}

	int* Eveniment::getLocuriOcupateTotal() {
		if (locuriOcupateTotal != nullptr) {
			return locuriOcupateTotal;
		}
	}

	int* Eveniment::getPreturi() {
		if (preturi != nullptr) {
			return preturi;
		}
	}

	void Eveniment::setDenumire(const char* denumire) {
		if (denumire != nullptr && Utils::hasOnlyLetters(denumire)) {
			if (this->denumire != nullptr) {
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
	};
	void Eveniment::setData(string data) {
		if (Utils::isValidDate(data)) {
			this->data = data;
		}
	};
	void Eveniment::setOra(string ora) {
		if (Utils::isValidHour(ora)) {
			this->ora = ora;
		}
	};
	void Eveniment::setLocatie(Locatie locatie) {
		if (locatie.isValid()) {
			delete l;
			l = new Locatie(locatie);
		}
	};
	void Eveniment::setPreturi(int* preturi,int nrPreturi) {
		if (preturi != nullptr && nrPreturi == l->getNrZone()) {
			for (int i = 0; i < l->getNrZone(); i++)
			{
				this->preturi[i] = preturi[i];
			}
		}
	}

	bool Eveniment:: hasValidPrices(Locatie locatie,int* preturi) {
		for (int i = 0; i < locatie.getNrZone(); i++)
		{
			if (!Utils::isNumber(to_string(preturi[i]))) {
				return false;
			}
		}
		return true;
	}

	//pentru a nu da eroare in anumite metode obiectul trebuie sa contina elemente valide
	bool Eveniment::hasValidData() {
		if (denumire == nullptr || data == "" || ora == "" || l == nullptr) {
			return false;
		}
		return true;
	}

	int Eveniment::getNrEvenimente() {
		return nrEvenimente;
	}

	//verifica daca data introdusa este in viitor
	bool  Eveniment::esteEvenimentInViitor(){
		if (data != "") {
			return Utils::esteDataInViitor(data);
		}
	}

	bool Eveniment::esteEvenimentValid() {
		if (l->isValid() && Utils::isValidDate(data) && locuriOcupateZona != nullptr 
			&& Utils::isValidHour(ora) && denumire != nullptr && Utils::hasOnlyLetters(denumire)) {
			return true;
		}
		return false;
	}

	Eveniment& Eveniment::operator=( Eveniment& e)
	{
		if (e.esteEvenimentValid()) {
			
			delete[] denumire;

			if (l != nullptr) {
				delete l;
			}

			delete[] locuriOcupateZona;

			delete[] locuriOcupateTotal;

			delete[] preturi;

			l = new Locatie(*e.l);
			data = e.data;
			ora = e.ora;
			denumire = new char[strlen(e.denumire) + 1];
			strcpy_s(denumire, strlen(e.denumire) + 1, e.denumire);

			locuriOcupateZona = new int[l->getNrZone()+1];
			for (int i = 0; i < l->getNrZone(); i++)
			{
				locuriOcupateZona[i] = e.getLocuriOcupateZona()[i];
			}

			locuriOcupateTotal = new int[l->nrLocuriRepartizate(l->getNrZone(),l->getNrLocuriZona()) + 1];
			for (int i = 0; i < l->nrLocuriRepartizate(l->getNrZone(), l->getNrLocuriZona()); i++)
			{
				locuriOcupateTotal[i] = e.locuriOcupateTotal[i];
			}

			preturi = new int[l->getNrZone() + 1];
			for (int i = 0; i < l->getNrZone(); i++)
			{
				preturi[i] = e.getPreturi()[i];
			}
		}
		else {
			cout << ("Nu se poate realiza copierea elementelor") << endl;
		}

		return *this;
	}

	

	Eveniment&  Eveniment::operator++() {
		if (ora != "") {
			if (ora.substr(0, 2) != "23") {
				int oraIntreg = stoi(ora.substr(0, 2));
				oraIntreg++;
				ora[0] = to_string(oraIntreg)[0];
				ora[1] = to_string(oraIntreg)[1];
			}
			else {
				ora[0] = '0';
				ora[1] = '0';
			}
		}
		return *this;
	}

	Eveniment& Eveniment::operator++(int a) {
		Eveniment copie = *this;
		if (ora != "") {
			if (ora.substr(0, 2) != "23") {
				int oraIntreg = stoi(ora.substr(0, 2));
				oraIntreg++;
				ora[0] = to_string(oraIntreg)[0];
				ora[1] = to_string(oraIntreg)[1];
			}
			else {
				ora[0] = '0';
				ora[1] = '0';
			}
		}
		return copie;
	}

	 Eveniment:: operator string() {
		string denumireString = denumire;
		return "Evenimentul " + denumireString + " are loc la data de " + data +
			" la ora " + ora + " in locatia " + l->getDenumire();
	}

	 void Eveniment::prelucrarePreturi(istream& in) {
		 for (int i = 0; i < l->getNrZone(); i++)
		 {
			 cout << "Introduceti pretul pentru " <<l->getZone()[i] << ": ";
			 string pret;
			 in >> pret;
			 if (Utils::isNumber(pret)) {
				 preturi[i] = stoi(pret);
			 }
			 else {
				 cout << "Preturi introdus este gresit " << endl;
				 i--;
			 }
		 }
	 }

	istream& operator>>(istream& in, Eveniment& e) {
		if (e.hasValidData()) {
			cout << "Denumirea evenimentului: ";
			string denumire;
			getline(in, denumire);
			if (Utils::hasOnlyLetters(denumire)) {
				cout << "Data evenimentului(dd.mm.yyyy): ";
				string data;
				in >> data;
				if (Utils::isValidDate(data)) {
					cout << "Ora evenimentului(hh:mm): ";
					string ora;
					in >> ora;
					if (Utils::isValidHour(ora)) {

						in >> (*e.l);

						e.prelucrarePreturi(in);

						delete[] e.denumire;
						e.denumire = new char[denumire.length() + 1];
						strcpy_s(e.denumire, denumire.length() + 1, denumire.c_str());

						delete[] e.locuriOcupateZona;
						e.locuriOcupateZona = new int[e.getLocatie().getNrZone() + 1];
						for (int i = 0; i < e.getLocatie().getNrZone(); i++)
						{
							e.locuriOcupateZona[i] = 0;
						}
						e.data = data;
						e.ora = ora;
					}
					else {
						cout << "Ora invalida" << endl;
					}
				}
				else {
					cout << "Data invalida" << endl;
				}
			}
			else {
				cout << "Denumire invalida" << endl;
			}
		}
		else {
			cout << "Evenimentul nu are date valide" << endl;
		}

		return in;
	}

	ostream& operator<<(ostream& out, Eveniment e) {
		if (e.hasValidData()) {
			out << "-----------------------" << endl;
			out << "Denumire eveniment: ";
			for (int i = 0; i < strlen(e.denumire); i++)
			{
				out << e.denumire[i];
			}
			out << endl;
			out << "Data evenimentului: " << e.data << endl;
			out << "Ora evenimentului: " << e.ora << endl;
			for (int i = 0; i < e.getLocatie().getNrZone(); i++)
			{
				out << "Numarul de locuri ocupate pentru zona " << i+1 << " este " << e.getLocuriOcupateZona()[i] << endl;
			}
			for (int i = 0; i < e.getLocatie().getNrZone(); i++)
			{
				out << e.getLocatie().getZone()[i] << " are pretul: " << e.preturi[i] << endl;;
			}
			out << "Locatia evenimentului: " << endl;
			out << "-----------------------" << endl << (*e.l) << "-----------------------" << endl;
		
		
		}
		else {
			cout << "Evenimentul nu are date valide" << endl;
		}
		return out;
	}
	