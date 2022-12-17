#include <iostream>
#include "Locatie.h"
#include "Eveniment.h"
#include "Bilet.h"




int main()
{
    string zone[4] = { "Loja 1", "Loja 2" };
    int nrLoc[4] = { 20,40 };
    string zone1[4] = { "Inel 1", "Inel 2" };
    int nrLoc1[4] = { 20,140 };
    string zone2[4] = { "Categoria A", "Categoria B", "Categoria C"};
    int nrLoc2[4] = { 10,40,80 };

    
    try {
        cout << "---------------------------------Validari Locatie--------------------------------------" << endl;
        Locatie loc1("Arene", 100, 2, zone, nrLoc);
        Locatie loc2("Carol", 500, 2, zone1, nrLoc1);
        Locatie loc3("Scena", 300, 3, zone2, nrLoc2);
        Locatie locatii[3] = { loc1, loc2, loc3 };

        loc2.setDetaliiZone(3, zone2, nrLoc2);

        cin >> loc2;

        cout << loc2.getDenumire() << endl;
        cout << loc2.getnrMaximLocuri() << endl;
        cout << loc2.getNrZone() << endl;
        for (int i = 0; i < loc2.getNrZone(); i++)
        {
            cout << loc2.getZone()[i] << " ";

        }
        cout << endl;
        for (int i = 0; i < loc2.getNrZone(); i++)
        {
            cout << loc2.getNrLocuriZona()[i] << " ";
        }
        cout << endl;

        cout << loc2;
        
        cout << "Cea mai mare locatie etse: " << endl;
         cout << Locatie::ceaMaiMareLocatie(locatii, 3);
        loc2 = loc1;
        cout << "Operatorul de indexare pentru localitatea 1 loc1[1]: " << loc1[1] << endl;;
        cout << "Verificare loc1 == loc2: " << (loc1 == loc2) << endl;;
      
        cout << "---------------------------------Validari Eveniment-------------------------------------" << endl;

        int preturi1[2] = { 30,100 };
        int preturi2[3] = {10, 30,100 };
        int preturi3[3] = { 200,140 ,500 };


        Eveniment e1("14.12.2025", "21:03", "Meci Fotbal", loc1,preturi1);
        Eveniment e2("16.12.2024", "21:00", "Untold", loc2, preturi1);
        Eveniment e3("22.10.2026", "22:00", "Piesa de teatru", loc3, preturi2);

        e2.setPreturi(preturi3 ,3);
        cout  << "Evenimentul 3 este: " << endl << e3;
        

        e2.setDenumire("Piesa de teatru");
        e2.setData("21.09.2023");
        e2.setOra("14:00");
        e2.setLocatie(loc2);

        cout << e1.getDenumire() <<endl;
        cout << e1.getData() << endl;
        cout << e1.getOra() << endl;
        cout << e1.getLocatie() << endl;
        

        e2 = ++e1;
        e2++;

        cout << "Numarul de evenimente este:" << e2.getNrEvenimente() << endl; //verificat
        cin >> e2;
        cout << (string)e2 << endl;

        cout << "---------------------------------Validari Bilet----------------------------------------" << endl;

        Bilet b1("Loja 2", 40, e1);
        Bilet b2("Loja 1",20,e1);
        Bilet b3("Categoria A", 100, e3);

        cin >> b3;
        cout << b3; 
       
        b2.setTipBilet("Peluza"); // nu modifica tipul
        b2.setTipBilet("Loja 2");
        b2.setLoc(1000); // nu modifica locul
        b2.setLoc(15);
        b2.setEveniment(e2);

        cout << b2.getTipBilet() << endl;
        cout << b2.getId() << endl;
        cout << b2.getLoc() << endl;
        cout << b2.getValidat() << endl;

        b2.valideaza();

        if (!b2) {
           cout << "Biletul este validat" << endl;
        }
        else {
            cout << "Biletul este nevalidat" << endl;
        }

        cout << "Locul lui b2 mai mic decat locul lui b1: " << (b3 < b2) << endl;
        cout << "Locul lui b2 mai mare decat locul lui b1: " << (b3 > b2) << endl;

    }
    catch (exception e) {
        cout << e.what();
    }
    
}
