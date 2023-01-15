#include "PrelucrareFisierText.h"
#include "PrelucrareFisierBinar.h"
#include "Meniu.h"
#include <string>
#include <list>
#include <iterator>


void PrelucrareFisierText::scriere(Bilet b)
{
}

void PrelucrareFisierText::scriere(Eveniment e)
{
}

void PrelucrareFisierText::scriere(Locatie l)
{
}

void PrelucrareFisierText::citireBilet()
{
    ifstream f;
    f.open(numeFisier);
    while (!f.eof()) {
        string s;
        f >> s;
        if (s == "b") {
           string tip;
           int loc;
           f >> ws;
           getline(f, tip);
           f >> loc;
            
           string data, ora, denumireEveniment;
           int nrPreturi;
           f >> data;
           f >> ora;
           f >> ws;
           getline(f, denumireEveniment);
           f >> nrPreturi;
           int* preturi = new int[nrPreturi];
           for (int i = 0; i < nrPreturi; i++)
           {
              f >> preturi[i];
           }
                
            string denumire;
            int nrMaxLocuri, nrZone;

            f >> denumire;
            f >> nrMaxLocuri;
            f >> nrZone;

            string* zone = new string[nrZone];
            int* nrLocuriZona = new int[nrZone];

            for (int i = 0; i < nrZone; i++)
            {
              f >> ws;
              getline(f, zone[i]);

            }
            for (int i = 0; i < nrZone; i++)
            {
              f >> nrLocuriZona[i];

            }
            bool evenimentCunoscut = false;
            for (int i = 0; i < Eveniment::getNrEvenimente(); i++){
              if ((*Eveniment::getEvenimente()[i]).getData() == data) {
                    Bilet b(tip, loc, *Eveniment::getEvenimente()[i]);
                    evenimentCunoscut = true;
                    Meniu::bileteDeSalvat->push_back(b);
               }
            }
            bool locatieCunoscuta = false;
            for (int i = 0; i < Locatie::getNrLocatii() && !evenimentCunoscut; i++)
            {
              if ((*Locatie::getLocatii()[i]).getDenumire() == denumire) {
                  Eveniment e(data, ora, denumireEveniment.c_str(), *Locatie::getLocatii()[i], preturi);
                  Bilet b(tip, loc, e);
                  locatieCunoscuta = true;
                  Meniu::bileteDeSalvat->push_back(b);
              }
            }
            if (!evenimentCunoscut && !locatieCunoscuta) {
                Locatie l(denumire, nrMaxLocuri, nrZone, zone, nrLocuriZona);
                Eveniment e(data, ora, denumireEveniment.c_str(), l, preturi);
                Bilet b(tip, loc, e);
                Meniu::bileteDeSalvat->push_back(b);
            }
        }
    }

}

void PrelucrareFisierText::citireEveniment()
{
    ifstream f;
    f.open(numeFisier);
    while (!f.eof()) {
        string s;
        f >> s;
        if (s == "e") {
            string data,ora,denumireEveniment;
            int nrPreturi;
            f >> data;
            f >> ora;
            f >> ws;
            getline(f, denumireEveniment);
            f >> nrPreturi;
            int* preturi = new int[nrPreturi];
            for (int i = 0; i < nrPreturi; i++)
            {
                f >> preturi[i];
            }
                string denumire;
                int nrMaxLocuri, nrZone;

                f >> denumire;
                f >> nrMaxLocuri;
                f >> nrZone;

                string* zone = new string[nrZone];
                int* nrLocuriZona = new int[nrZone];

                for (int i = 0; i < nrZone; i++)
                {
                    f >> ws;
                    getline(f, zone[i]);

                }
                for (int i = 0; i < nrZone; i++)
                {
                    f >> nrLocuriZona[i];

                }
                bool locatieCunoscuta = false;
                for (int i = 0; i < Locatie::getNrLocatii(); i++)
                {

                    if ((*Locatie::getLocatii()[i]).getDenumire() == denumire) {
                        Eveniment e(data, ora, denumireEveniment.c_str(), *Locatie::getLocatii()[i], preturi);
                        locatieCunoscuta = true;

                        Meniu::evenimenteDeSalvat->push_back(e);
                    }
                }
                if (!locatieCunoscuta) {
                    Locatie l(denumire, nrMaxLocuri, nrZone, zone, nrLocuriZona);
                    Eveniment e(data, ora, denumireEveniment.c_str(), l, preturi);
                    Meniu::evenimenteDeSalvat->push_back(e);
                }  
        }
    }
}

void PrelucrareFisierText::citireLocatie()
{
    ifstream f;
    f.open(numeFisier);
    while (!f.eof()) {
        string s;
        f >> s;
        if (s == "l") {
            string denumire;
            int nrMaxLocuri, nrZone;

            f >> denumire;
            f >> nrMaxLocuri;
            f >> nrZone;
            
            string* zone = new string[nrZone];
            int* nrLocuriZona = new int[nrZone];

            for (int i = 0; i < nrZone; i++)
            {
                f >> ws;
                getline(f, zone[i]);

            }
            for (int i = 0; i < nrZone; i++)
            {
                f >> nrLocuriZona[i];

            }
            Locatie l(denumire, nrMaxLocuri, nrZone, zone, nrLocuriZona);
            PrelucrareFisierBinar pfb;
            pfb.scriere(l);
        }
    }
}

void PrelucrareFisierText::citire(string numeFisier) {
    bool fisierCitit = false;

     list<string>::iterator it;
     for (it = PrelucrareFisierBinar::fisierCitite->begin(); it != PrelucrareFisierBinar::fisierCitite->end(); ++it) {
         if (*it == numeFisier) {
             fisierCitit = true;
        }
     }

     if (!fisierCitit) {
         this->numeFisier = numeFisier;

         ifstream f;
         f.open(numeFisier);
         if (valideazaFisier() && f.is_open()) {
             f.close();

             citireLocatie();
             citireEveniment();
             citireBilet();

             PrelucrareFisierBinar::fisierCitite->push_back(numeFisier);

             for (int i = 0; i < Locatie::getNrLocatii(); i++)
             {
                 cout << *Locatie::getLocatii()[i];
             }
           
             for (int i = 0; i < Eveniment::getNrEvenimente(); i++)
             {
                 cout << *Eveniment::getEvenimente()[i];
             }
             for (int i = 0; i < Bilet::getNrBilete(); i++)
             {
                 cout << *Bilet::getBilete()[i];
             }
         }
         else {
             cout << "Fisierul introdus nu este valid" << endl;
         }
     }
     else {
         cout << "Ati citit deja din acest fisier" << endl;
     }
   
}


bool PrelucrareFisierText::valideazaFisier()
{
    if (numeFisier.substr(numeFisier.length() - 4, 4) != ".txt") {
        return false;
    }
    return true;
}






