#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 
#include "Bilet.h"
using namespace std;

int Bilet::nrBilete = 0;

	Bilet::Bilet() : id(-1) {
		tipBilet = "";
		loc = -1;
		validat = false;
		pret = -1;

		nrBilete++;
	}

	Bilet::Bilet(string tipBilet,int loc,Eveniment& e) : id(creazaId()) {
		if ( esteTipBiletValid(tipBilet,e) && e.esteEvenimentValid() 
			&& esteLocValid(loc,tipBilet,e)) { 
			this->tipBilet = tipBilet;
			this->loc = loc;
			validat = false;
			eveniment = e;
			seteazaPret(tipBilet);
		}
		else {
			throw exception("Date invalide ale biletului");
		}

		nrBilete++;
		
	}

	Bilet::Bilet(Bilet& b) :id(creazaId()) {
		tipBilet = b.tipBilet;
		loc = b.loc;
		validat = b.validat;
		eveniment = b.eveniment;
		pret = b.pret;
	}

	int Bilet::getPret() {
		if (pret > 0) {
			return pret;
		}
	}

	string Bilet::getTipBilet() {
		if (tipBilet != "") {
			return tipBilet;
		}
		else {
			cout << "Tip bilet invalid" << endl;
		}
	};

	long Bilet::getId() {
		if (id != -1) {
			return id;
		}
		else {
			cout << "Id invalid" << endl;
		}
	};

	int Bilet::getLoc() {
		if (loc != -1) {
			return loc;
		}
		else {
			cout << "Loc invalid" << endl;
		}
	};

	bool Bilet::getValidat() {
		return validat;
	};

	Eveniment Bilet::getEveniment() {
		if (eveniment.getDenumire() != nullptr) {
			return eveniment;
		}
		else {
			cout << "Eveniment invalid" << endl;
		}
	};

	void Bilet::setTipBilet(string tip) {
		if (eveniment.hasValidData() && esteTipBiletValid(tip, eveniment)) {
			tipBilet = tip;
		}
	};

	void Bilet::setLoc(int loc) {
		if (eveniment.hasValidData() && esteLocValid(loc,tipBilet, eveniment)) {
			this->loc = loc;
		}
	};

	void Bilet::setEveniment(Eveniment e) {
		if (e.hasValidData() && esteTipBiletValid(tipBilet,e) && esteLocValid(loc,tipBilet,e)) {
			eveniment = e;
			seteazaPret(tipBilet);
		}
	};

	void Bilet::seteazaPret(string tipBilet) {
		for (int i = 0; i < eveniment.getLocatie().getNrZone(); i++)
		{
			if (tipBilet == eveniment.getLocatie().getZone()[i]) {
				pret = eveniment.getPreturi()[i];
				break;
			}
		}
	}

	//tipul coincide cu una din zonele din locatie
	bool Bilet::esteTipBiletValid(string tipBilet,Eveniment e) {

		if (tipBilet != "") {
			for (int i = 0; i < e.getLocatie().getNrZone(); i++)
			{
				if (tipBilet == e.getLocatie().getZone()[i]) {					
					return true;
				}
			}
		}
		cout << "Tipul biletului nu este valid" << endl;
		return false;
	}


	bool Bilet::locDisponibil(int loc, string tipBilet, Eveniment& e) {
		int i;
		for (i = 0; i < e.getLocatie().getNrZone(); i++)
		{
			if (tipBilet == e.getLocatie().getZone()[i]) {
				//verifica daca mai sunt locuri in zona respectiva
				if (e.getLocuriOcupateZona()[i] + 1 < e.getLocatie().getNrLocuriZona()[i]) {
					//verifica daca locul este deja ocupat
					if (e.getLocuriOcupateTotal()[loc] != 1) {
						e.getLocuriOcupateZona()[i]++;
						e.getLocuriOcupateTotal()[loc] = 1;
						return true;
					}
					else {
						cout << "Locul este deja ocupat " << endl;
						return false;
					}
				}
				else {
					cout << "Nu mai sunt locuri disponibile in acea zona" << endl;
					return false;
				}
			}
		}
		//in caz ca metoda este folosita fara esteTipBiletValid(), iar tipul este invalid
		return false;
	}

	bool Bilet::esteLocValid(int loc,string tipBilet,Eveniment& e) {
		if (loc > 0 && loc <= e.getLocatie().nrLocuriRepartizate(e.getLocatie().getNrZone(),e.getLocatie().getNrLocuriZona()) 
			&& locDisponibil(loc,tipBilet,e)) {
			return true;
		}
		return false;
	}

	long Bilet::creazaId() {
		srand(time(0));
		long id = rand() % 1000 * (nrBilete + 1);


		return id;
	}

	bool Bilet::operator!()
	{
		return validat;
	}

	bool Bilet::operator>(Bilet b1)
	{
		return loc > b1.loc;
	}

	bool Bilet::operator<(Bilet b1)
	{
		return loc < b1.loc;
	}

	void Bilet::valideaza() {
		if (validat == false && loc != -1 && tipBilet != "" && eveniment.hasValidData()) {
			validat = !validat;
		}
		else {
			cout << "Bilet deja validat" << endl;
		}
	}

	istream& operator>>(istream& in, Bilet& l) {

		in >> l.eveniment;
		if (l.eveniment.hasValidData()) {
			cout << "Introduceti tipul biletului: ";
			string tip;
			in.ignore();
			getline(in,tip);
			if (l.esteTipBiletValid(tip, l.eveniment)) {
				int loc;
				cout << "Introduceti locul(mai mic decat locurile repartizate deoarece repartizarea se face din fata locatiei): ";
				in >> loc;
				if (l.esteLocValid(loc, tip, l.eveniment)) {
					l.tipBilet = tip;
					l.loc = loc;
					l.seteazaPret(tip);
				}
				else {
					cout << "Locul depaseste numarul de locuri din zonele introduse" << endl;
				}
			}
			else {
				cout << "Tip bilet invalid " << endl;
			}
		}
		else {
			cout << "Eveniment invalid " << endl;
		}

		return in;
	 };
	ostream& operator<<(ostream& out, Bilet b) {
		cout << endl;
		out << "Tipul biletului este " << b.tipBilet << endl;
		out << "Id-ul este: " << b.id << endl;
		out << "Locul este: " << b.loc << endl;
		out << "Pretul este: " << b.pret << endl;
		if (b.validat) {
			out << "Biletul este validat " << endl;
		}
		else {
			out << "Biletul este nevalidat " << endl;
		}
		out  << b.eveniment;

		return out;
	 };


