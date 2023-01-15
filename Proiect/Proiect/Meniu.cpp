#include "Meniu.h"
#include "Utils.h"
#include "Bilet.h"
#include "string"
#include "PrelucrareFisierBinar.h"
#include<iostream>
using namespace std;

vector<Eveniment>* Meniu::evenimenteDeSalvat = new vector<Eveniment>();
vector<Bilet>* Meniu::bileteDeSalvat = new vector<Bilet>();

Meniu::Meniu() {

	cout << "------------------------Meniu----------------------" << endl;
	cout << "Ce doriti sa faceti?" << endl;
	cout << "1) Scriere" << endl;
	cout << "2) Prelucrare date" << endl;
	cout << "3) Iesire din meniu" << endl;
	cout << "Numar/Denumire:";
	string functionalitate;
	cin >> ws;
	getline(cin, functionalitate);
	cout << endl;
	if (functionalitate == "1" || Utils::toLowerCase(functionalitate) == "scriere") {
		scriere();
	}
	else if(functionalitate == "2" || Utils::toLowerCase(functionalitate) == "prelucrare date") {
		citire();
	}
	else if (functionalitate == "3" || Utils::toLowerCase(functionalitate) == "iesire din meniu") {

	}
	else {
		cout << "Nu ati scris un numar sau o denumire corect :(" << endl;
	}
}

void Meniu :: citire() {
	cout << "Ce doriti sa prelucrati:" << endl;
	cout << "1) Locatie" << endl;
	cout << "2) Eveniment" << endl;
	cout << "3) Bilet" << endl;
	cout << "4) Intoarcere la meniu" << endl;
	cout << "Numar/Denumire:";
	string deCitit;
	cin >> deCitit;
	cout << endl;
	if (deCitit == "1" || Utils::toLowerCase(deCitit) == "locatie") {
		if (Locatie::getNrLocatii() != 0) {

			cout << "Locatiile deja existente sunt:" << endl;

			for (int i = 0; i < Locatie::getNrLocatii(); i++)
			{
				cout << i + 1 << ") " << Locatie::getLocatii()[i]->getDenumire() << endl;
			}

			cout << "Optiuni: " << endl;
			cout << "1) Doriti sa vedeti o locatie mai detaliat" << endl;
			cout << "2) Doriti sa vedeti care locatie este cea mai mare" << endl;
			cout << "3) Doriti sa vedeti cate locuri nerepartizate mai sunt" << endl;
			cout << "4) Intoarcere la meniu" << endl;
			cout << "Numar:";
			cin >> deCitit;
			cout << endl;

			if (deCitit == "1") {
				cout << "Scrieti numarul sau numele corespunzator locatiei pe care dotiti sa-l vedeti: ";
				cin >> deCitit;
				cout << endl;
				if (Utils::isNumber(deCitit) && stoi(deCitit) <= Locatie::getNrLocatii()) {
					cout << *Locatie::getLocatii()[stoi(deCitit) - 1];
				}
				else {
					cautareDupaNume(deCitit, "locatie");
				}
			}
			else if (deCitit == "2") {
				cout << "Locatia cu cel mai mare numar de locuri este: " << endl;
				cout << Locatie::ceaMaiMareLocatie(Locatie::getLocatii(), Locatie::getNrLocatii());
				cout << endl;
			}
			else if (deCitit == "3") {
				for (int i = 0; i < Locatie::getNrLocatii(); i++)
				{
					int locuriRamase = Locatie::getLocatii()[i]->getnrMaximLocuri() - Locatie::getLocatii()[i]->
					nrLocuriRepartizate(Locatie::getLocatii()[i]->getNrZone(), Locatie::getLocatii()[i]->getNrLocuriZona());
					cout << Locatie::getLocatii()[i]->getDenumire() << " mai are " << locuriRamase << " locuri nerepartizate" << endl;
				}
			}
			else if (deCitit == "4" || Utils::toLowerCase(deCitit) == "intoarcere la meniu") {
				Meniu m;
			}
			else {
				cout << "Nu ati introdus un introdus un numar sau denumirea :(" << endl;
			}
			
		}
		else {
			cout << "Nu exista locatii deocamdata, aveti optiunea de a citi din fisier sau de la tastatura" << endl;
		}
		
	}
	else if (deCitit == "2" || Utils::toLowerCase(deCitit) == "eveniment") {
		if (Eveniment::getNrEvenimente() != 0) {
			cout << "Evenimentele deja existente sunt:" << endl;
			for (int i = 0; i < Eveniment::getNrEvenimente(); i++)
			{
				cout << i + 1 << ") " << Eveniment::getEvenimente()[i]->getDenumire() << endl;
			}

			cout << "Optiuni: " << endl;
			cout << "1) Doriti sa vedeti un eveniment mai detaliat" << endl;
			cout << "2) Doriti sa amanati un eveniment cu o ora" << endl;
			cout << "3) Doriti o descriere scurta a evenimentelor" << endl;
			cout << "4) Intoarcere la meniu" << endl;
			cout << "Numar:";
			cin >> deCitit;
			cout << endl;
		
			if (deCitit == "1" && stoi(deCitit) <= Eveniment::getNrEvenimente()) {
				cout << "Scrieti numarul sau numele corespunzator evenimentului pe care dotiti sa-l vedeti: ";
				cin >> deCitit;
				cout << endl;
				if (Utils::isNumber(deCitit) && stoi(deCitit) <= Eveniment::getNrEvenimente()) {
					cout << *Eveniment::getEvenimente()[stoi(deCitit) - 1];
				}
				else {
					cautareDupaNume(deCitit, "eveniment");
				}
			}
			else if (deCitit == "2") {
				cout << "Scrieti numarul corespunzator evenimentului pe care dotiti sa-l amanati: ";
				cin >> deCitit;
				cout << endl;
				if (Utils::isNumber(deCitit) && stoi(deCitit) <= Eveniment::getNrEvenimente()) {
					(* Eveniment::getEvenimente()[stoi(deCitit) - 1])++;
				}
			}
			else if (deCitit == "3") {
				for (int i = 0; i < Eveniment::getNrEvenimente(); i++)
				{
					cout << (string)*Eveniment::getEvenimente()[i] << endl;
				}
			}
			else if (deCitit == "4" || Utils::toLowerCase(deCitit) == "intoarcere la meniu") {
				Meniu m;
			}
			else {
				cout << "Nu ati introdus un numar sau denumirea :(" << endl;
			}
		}
		else {
			cout << "Nu exista evenimente deocamdata, aveti optiunea de a citi din fisier sau de la tastatura" << endl;
		}
		
	}
	else if (deCitit == "3" || Utils::toLowerCase(deCitit) == "bilet") {
		if (Bilet::getNrBilete() != 0) {
			cout << "Biletele deja existente sunt:" << endl;
			for (int i = 0; i < Bilet::getNrBilete(); i++)
			{
				cout << i + 1 << ") " << Bilet::getBilete()[i]->getTipBilet() 
					<< " cu locul: " << Bilet::getBilete()[i]->getLoc() << endl;
			}
			cout << "Optiuni: " << endl;
			cout << "1) Doriti sa vedeti un bilet mai detaliat" << endl;
			cout << "2) Doriti sa validati un bilet " << endl;
			cout << "3) Doriti sa comparati locurile a doua bilete " << endl;
			cout << "4) Intoarcere la meniu" << endl;
			cout << "Numar:";
			cin >> deCitit;
			cout << endl;
			if (deCitit == "1") {
				cout << "Scrieti numarul sau numele (tipul) corespunzator biletului pe care dotiti sa-l vedeti: ";
				cin >> ws;
				getline(cin, deCitit);
				cout << endl;
				if (Utils::isNumber(deCitit) && stoi(deCitit) <= Bilet::getNrBilete()) {
					cout << *Bilet::getBilete()[stoi(deCitit) - 1];
				}
				else {
					cautareDupaNume(deCitit, "bilet");
				}
			}
			else if (deCitit == "2") {
				cout << "Scrieti numarul corespunzator biletului pe care dotiti sa-l validati: ";
				cin >> deCitit;
				cout << endl;
				if (Utils::isNumber(deCitit) && stoi(deCitit) <= Bilet::getNrBilete()) {
					Bilet::getBilete()[stoi(deCitit) - 1]->valideaza();

					for (int i = 0; i < Meniu::bileteDeSalvat->size(); i++)
					{
						if (Meniu::bileteDeSalvat->at(i).getTipBilet() == Bilet::getBilete()[stoi(deCitit) - 1]->getTipBilet()) {
							 Meniu::bileteDeSalvat->at(i).valideaza();
						}
					}
				}
			}
			else if (deCitit == "3") {
				string nr1, nr2;
				cout << "Numarul primului bilet:";
				cin >> nr1;
				cout << "Numarul celui de-al doilea bilet:";
				cin >> nr2;
				if (Utils::isNumber(nr1) && Utils::isNumber(nr2)
					&& stoi(nr1) <= Bilet::getNrBilete() && stoi(nr2) <= Bilet::getNrBilete() && nr1 != nr2) {
					if ((*Bilet::getBilete()[stoi(nr1) - 1]) < (*Bilet::getBilete()[stoi(nr2) - 1])) {
						cout << "Biletul " << nr1 << " are loc mai in fata, in comparatie cu biletul " << nr2 << endl;
					}
					else {
						cout << "Biletul " << nr2 << " are loc mai in fata, in comparatie cu biletul " << nr1 << endl;
					}
				}
				else {
					cout << "Numere invalide" << endl;
				}
			}
			else if (deCitit == "4" || Utils::toLowerCase(deCitit) == "intoarcere la meniu") {
				Meniu m;
			}
			else {
				cout << "Nu ati introdus un numar sau denumirea :(" << endl;
			}
		}
		else {
			cout << "Nu exista bilete deocamdata, aveti optiunea de a citi din fisier sau de la tastatura" << endl;
		}
		
	}
	else if (deCitit == "4" || Utils::toLowerCase(deCitit) == "intoarcere la meniu") {
		Meniu m;
	}
	else {
		cout << "Nu ati introdus un numar sau denumirea :(" << endl;
	}
}

void Meniu::scriere() {
	cout << "Ce doriti sa scrieti:" << endl;
	cout << "1) Locatie" << endl;
	cout << "2) Eveniment" << endl;
	cout << "3) Bilet" << endl;
	cout << "4) Intoarcere la meniu" << endl;
	cout << "Numar/Denumire:";
	string deScris;
	cin >> deScris;
	cout << endl;

	try {
		if (deScris == "1" || Utils::toLowerCase(deScris) == "locatie") {
			//locatie
			string denumire, nrMaximLocuri , nrZone ;
			cout << "Introduceti denumire locatiei: ";
			cin >> ws;
			getline(cin,denumire);

			do {
				cout << "Introduceti numarul maxim de locuri a locatiei: ";
				cin >> nrMaximLocuri;
			} while (!Utils::isNumber(nrMaximLocuri));

			do {
				cout << "Numarul de zone: ";
				cin >> nrZone;
			} while (!Utils::isNumber(nrZone) );

			if (stoi(nrZone) > 0) {
				string* zone = new string[stoi(nrZone)];
				int* nrLocuriZona = new int[stoi(nrZone)];

				zone = prelucrareZone(stoi(nrZone));
				nrLocuriZona = prelucrareNrLocuriZona(stoi(nrZone), stoi(nrMaximLocuri));

				Locatie l(denumire, stoi(nrMaximLocuri), stoi(nrZone), zone, nrLocuriZona);
				cout << "Doriti sa salvati datele intr-un fisier?" << endl;
				cout << "1)Da" << endl;
				cout << "2)Nu" << endl;
				cout << "Numar/Denumire:";
				string salvare;
				cin >> salvare;
				cout << endl;
				if (salvare == "1" || Utils::toLowerCase(salvare) == "da") {
					PrelucrareFisierBinar pfb;
					pfb.scriere(l);
				}
			}
			else {
				cout << "Numarul de zone nu poate sa fie 0" << endl;
			}
			
		}
		else if (deScris == "2" || Utils::toLowerCase(deScris) == "eveniment") {
			string denumire, nrMaximLocuri, nrZone;
			
			if (Locatie::getNrLocatii() != 0) {
				cout << "Doriti sa folositi o locatie deja existenta? " << endl;
				cout << "1)Da" << endl;
				cout << "2)Nu" << endl;
				cout << "Numar/Denumire:";
				cin >> deScris;
				cout << endl;
			}
			else {
				deScris = "2";
			}

				//eveniment
			if (deScris == "2" || Utils::toLowerCase(deScris) == "nu") {

				cout << "Introduceti denumire locatiei: ";
				cin >> ws;
				getline(cin, denumire);

				do {
					cout << "Introduceti numarul maxim de locuri a locatiei: ";
					cin >> nrMaximLocuri;
				} while (!Utils::isNumber(nrMaximLocuri));

				do {
					cout << "Numarul de zone: ";
					cin >> nrZone;
				} while (!Utils::isNumber(nrZone));

				if (stoi(nrZone) > 0) {
					string* zone = new string[stoi(nrZone)];
					int* nrLocuriZona = new int[stoi(nrZone)];
					zone = prelucrareZone(stoi(nrZone));
					nrLocuriZona = prelucrareNrLocuriZona(stoi(nrZone), stoi(nrMaximLocuri));

					Locatie l(denumire, stoi(nrMaximLocuri), stoi(nrZone), zone, nrLocuriZona);

					string denumire, data, ora;
					prelucrareDateEveniment(denumire, data, ora);

					int* preturi = new int[stoi(nrZone)];
					preturi = prelucrarePreturi(zone, stoi(nrZone));
					Eveniment e(data, ora, denumire.c_str(), l, preturi);

					salvareFisier(e);
				}
				else {
					cout << "Numarul de zone nu poate sa fie 0" << endl;
				}

			}else{
				cout << "Locatiile deja existente sunt:" << endl;

				for (int i = 0; i < Locatie::getNrLocatii(); i++)
				{
					cout << i + 1 << ") " << Locatie::getLocatii()[i]->getDenumire() << endl;
				}
				bool numeValid = false;
				int i;
				while (numeValid == false) {
					string numeLocatie;
					cout << "Introduceti numele locatiei pe care doriti sa o folisti:";
					cin >> ws;
					getline(cin, numeLocatie);
					for (i = 0; i < Locatie::getNrLocatii(); i++)
					{
						if (Locatie::getLocatii()[i]->getDenumire() == numeLocatie) {
							break;
						}
					}
					if (i != Locatie::getNrLocatii()) {
						numeValid = true;
					}
				}
					cout << (* Locatie::getLocatii()[i]);

					string denumire, data, ora;
					prelucrareDateEveniment(denumire, data, ora);

					int* preturi = new int[Locatie::getLocatii()[i]->getNrZone()];
					preturi = prelucrarePreturi(Locatie::getLocatii()[i]->getZone(), Locatie::getLocatii()[i]->getNrZone());
					Eveniment e(data, ora, denumire.c_str(), (*Locatie::getLocatii()[i]), preturi);

					salvareFisier(e);
				
			}
	
		}
		else if (deScris == "3" || Utils::toLowerCase(deScris) == "bilet") {
			//bilet
			if (Eveniment::getNrEvenimente() != 0) {
				cout << "Doriti sa folositi un eveniment deja existent:" << endl;
				cout << "1)Da" << endl;
				cout << "2)Nu" << endl;
				cout << "Numar/Denumire:";
				cin >> deScris;
				cout << endl;
			}
			else {
				deScris = "2";
			}

			if (deScris == "2" || Utils::toLowerCase(deScris) == "nu") {
				string denumire, nrMaximLocuri, nrZone;
				
				cout << "Introduceti denumire locatiei: ";
				cin >> ws;
				getline(cin, denumire);

				do {
					cout << "Introduceti numarul maxim de locuri a locatiei: ";
					cin >> nrMaximLocuri;
				} while (!Utils::isNumber(nrMaximLocuri));

				do {
					cout << "Numarul de zone: ";
					cin >> nrZone;
				} while (!Utils::isNumber(nrZone) );

				if (stoi(nrZone) > 0) {
					string* zone = new string[stoi(nrZone)];
					int* nrLocuriZona = new int[stoi(nrZone)];
					zone = prelucrareZone(stoi(nrZone));
					nrLocuriZona = prelucrareNrLocuriZona(stoi(nrZone), stoi(nrMaximLocuri));
					Locatie l(denumire, stoi(nrMaximLocuri), stoi(nrZone), zone, nrLocuriZona);

					string denumireEveniment, data, ora;
					prelucrareDateEveniment(denumire, data, ora);

					int* preturi = new int[stoi(nrZone)];
					preturi = prelucrarePreturi(zone, stoi(nrZone));

					Eveniment e1(data, ora, denumireEveniment.c_str(), l, preturi);
					prelucrareDateBilet(e1);
				}
				else {
					cout << "Numarul de zone nu poate sa fie 0" << endl;
				}
			}
			else {
				cout << "Evenimentele deja existente sunt:" << endl;
				for (int i = 0; i < Eveniment::getNrEvenimente(); i++)
				{
					cout << i + 1 << ") " << Eveniment::getEvenimente()[i]->getDenumire() << endl;
				}
				bool numeValid = false;
				int i;
				while (numeValid == false) {
					cout << "Introduceti numele evenimentului pe care doriti sa-l folositi:";
					string numeEveniment;
					cin >> ws;
					getline(cin, numeEveniment);
					
					for (i = 0; i < Eveniment::getNrEvenimente(); i++)
					{
						if (Eveniment::getEvenimente()[i]->getDenumire() == numeEveniment) {
							 break;
						}
					}

					if (i != Eveniment::getNrEvenimente()) {
						numeValid = true;
					}
				}
				cout << (*Eveniment::getEvenimente()[i]);
				prelucrareDateBilet(*Eveniment::getEvenimente()[i]);
			}
			
		}
		else if (deScris == "4" || Utils::toLowerCase(deScris) == "intoarcere la meniu") {
			Meniu m;
		}
		else {
		cout << "Nu ati introdus un numar sau denumirea :(" << endl;
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

	string* Meniu::prelucrareZone(int nr) {
		string zona;
		string* zone = new string[nr];
		for (int i = 0; i < nr; i++)
		{
			cout << " Denumire zona " << i + 1 << ": ";
			cin >> ws;
			getline(cin, zona);
			if (zona == "") {
				i--;
				cout << "Zona introdusa invalida!" << endl;
			}
			else {
				zone[i] = zona;
			}
		}
		return zone;
	}

	int* Meniu::prelucrareNrLocuriZona( int nr,int nrMaximLocuri) {
		string nrLocuri;
		int* nrLocuriZona = new int[nr];
		int suma = 0;
		for (int i = 0; i < nr; i++)
		{
			cout << "Numarul de locuri pentru zona " << i + 1 << ": ";
			cin >> nrLocuri;
			cin.ignore();

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
		return nrLocuriZona;
	}

	int* Meniu::prelucrarePreturi(string* zone,int nrZone) {
		int* preturi = new int[nrZone];
		for (int i = 0; i < nrZone; i++)
		{
			cout << "Introduceti pretul pentru " << zone[i] << ": ";
			string pret;
			cin >> pret;
			if (Utils::isNumber(pret)) {
				preturi[i] = stoi(pret);
			}
			else {
				cout << "Preturi introdus este gresit " << endl;
				i--;
			}
		}
		return preturi;
	}

	void Meniu::prelucrareDateEveniment(string& denumire, string& data, string& ora) {
		cout << "Denumirea evenimentului: ";
		cin >> ws;
		getline(cin, denumire);
		do {
			cout << "Data evenimentului(dd.mm.yyyy): ";
			cin >> ws;
			getline(cin, data);
		} while (!Utils::isValidDate(data) );
		do {
			cout << "Ora evenimentului(hh:mm): ";
			cin >> ws;
			getline(cin, ora);
		} while (!Utils::isValidHour(ora));
	}

	void Meniu::salvareFisier(Eveniment e) {
		cout << "Doriti sa salvati datele intr-un fisier?" << endl;
		cout << "1)Da" << endl;
		cout << "2)Nu" << endl;
		cout << "Numar/Denumire:";
		string salvare;
		cin >> salvare;
		cout << endl;
		if (salvare == "1" || Utils::toLowerCase(salvare) == "da") {
			evenimenteDeSalvat->push_back(e);
		}
	}

	void Meniu::prelucrareDateBilet(Eveniment e) {
		cout << "Introduceti tipul biletului(o zona din locatie): ";
		string tip;
		cin >> ws;
		getline(cin, tip);
		string loc;
		do {
			cout << "Introduceti locul(mai mic decat locurile repartizate deoarece repartizarea se face din fata locatiei): ";
			cin >> loc;
		} while (!Utils::isNumber(loc));

		Bilet b(tip, stoi(loc), e);

		cout << "Doriti sa salvati datele intr-un fisier?" << endl;
		cout << "1)Da" << endl;
		cout << "2)Nu" << endl;
		cout << "Numar/Denumire:";
		string salvare;
		cin >> salvare;
		cout << endl;
		if (salvare == "1" || Utils::toLowerCase(salvare) == "da") {
			bileteDeSalvat->push_back(b);
		}
	}

	void Meniu::cautareDupaNume(string nume, string tip) {
		if (tip == "locatie") {
			for (int i = 0; i < Locatie::getNrLocatii(); i++)
			{
				if (Locatie::getLocatii()[i]->getDenumire() == nume) {
					cout << (*Locatie::getLocatii()[i]);
					break;
				}
			}
		}
		else if (tip == "eveniment") {
			for (int i = 0; i < Eveniment::getNrEvenimente(); i++)
			{
				if (Eveniment::getEvenimente()[i]->getDenumire() == nume) {
					cout << (*Eveniment::getEvenimente()[i]);
					break;
				}
			}
		}
		else {
			for (int i = 0; i < Bilet::getNrBilete(); i++)
			{
				if (Bilet::getBilete()[i]->getTipBilet() == nume) {
					cout << (*Bilet::getBilete()[i]);
					break;
				}
			}
		}
	}

	void Meniu::salvare() {
		PrelucrareFisierBinar pfb;
		pfb.scriereBileteEvenimente();
	}
