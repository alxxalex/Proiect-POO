#include <iostream>
#include "Bilet.h"
#include "Meniu.h"
#include "PrelucrareFisierText.h"
#include "PrelucrareFisierBinar.h"
#include "Utils.h"

int main()
{

    bool isRunning = true;
    PrelucrareFisierBinar pfb;
    pfb.citire();

    while (isRunning) {
        string tipCitire;
            cout << "Doriti sa cititi date din fisier sau sa intrati in meniu: ";
            cin >> tipCitire;
         if (Utils::toLowerCase(tipCitire) == "meniu") {
             Meniu m;
         }
         else if (Utils::toLowerCase(tipCitire) == "fisier") {
            string numeFisier;
            cout << "Fisierele existente sunt: " << endl << "1) date.txt" << endl << "2) date1.txt"
                << endl << "3) date2.txt" << endl;
            cout << "Introduceti numele fisierului din care vreti sa cititi:" << endl;
            cin >> numeFisier;
            PrelucrareFisierText pft;
            pft.citire(numeFisier);
            PrelucrareFisierBinar :: numeFisier = numeFisier;
            pfb.scriereFisiereCitite();
         }
         else {
             cout << "Nu ati scris fisier sau meniu " << endl;
         }
         string s;
         do {
             cout << "Doriti sa mai realizati alte actiuni ?" << endl;
             cout << "1) Da" << endl;
             cout << "2) Nu" << endl;
             cout << "Numar/Denumire:";
             cin >> s;
             if (s == "1" || Utils::toLowerCase(s) == "da" || s == "2" || Utils::toLowerCase(s) == "nu") {
                 break;
             }
         } while (true);
        if (s != "1" &&  Utils::toLowerCase(s) != "da") {
            
            isRunning = false;
            PrelucrareFisierBinar pfb;
            pfb.scriereBileteEvenimente();
        }
    }
    
    //bilet validat 

}
