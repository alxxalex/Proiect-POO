#include<iostream>
#include<string>
#include "Utils.h"
#include<ctime>
using namespace std;
#pragma warning(disable:4996)


	 bool Utils::isNumber(string nrString) {
		for (int i = 0; i < nrString.length(); i++)
		{
			if (nrString[i] < '0' || nrString[i] > '9') {
				return false;
			}
		}
		return true;
	 }

	 bool Utils::hasOnlyLetters(string s) {
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] < 'A' || s[i] > 'z' || (s[i] > 'Z' && s[i] < 'a')) {
				if (s[i] != ' ') {
					return false;
				}
			}
		}
		return true;
	 }

	 bool Utils:: isValidDate(string data) {
		
		if (data.length() == 10) {
			string ziua = data.substr(0, 2);
			string luna = data.substr(3, 2);
			string an = data.substr(6, 4);
			if (isNumber(ziua) && isNumber(luna) && isNumber(an)) {
				if (stoi(ziua) > 31) {

					cout << "Zi mai mare de 31" << endl;
					return false;
				}
				if (stoi(luna) > 12) {
					cout << "Luna mai mare de 12" << endl;
					return false;
				}
				if (data[2] != '.' || data[5] != '.') {
					cout << "Data nu este de forma dd.mm.yyyy" << endl;
					return false;
				}
				if (!esteDataInViitor(data)) {
					cout << "Data introdusa nu se afla in viitor" << endl;
					return false;
				}
				return true;
			}

			cout << "Data nu este de forma dd.mm.yyyy" << endl;
			return false;


		}

		cout << "Data nu este de forma dd.mm.yyyy" << endl;
		return false;
	}

	bool Utils :: isValidHour(string s) {
		if (s.length() == 5) {
			string ora = s.substr(0, 2);
			string minut = s.substr(3, 2);
			if (isNumber(ora) && isNumber(minut)) {
				if (stoi(ora) > 23) {
					cout << "Ora introdusa este invalida" << endl;
					return false;
				}
				if (stoi(minut) > 59) {
					cout << "Minutul introdus este invalid" << endl;
					return false;
				}
				if (s[2] != ':') {
					cout << "Ora nu este de forma hh:mm" << endl;
					return false;
				}
				return true;
			}
			cout << "Ora nu este de forma hh:mm" << endl;
			return false;
		}
		cout << "Ora nu este de forma hh:mm" << endl;
		return false;
	}
	
	//verifica daca data introdusa este dupa cea curenta sau nu
	 bool Utils:: esteDataInViitor(string dataEv) {
		time_t now = time(0);

		char data[100];
		//stocare in array a obiectului now cu forma %d.%m.%Y
		strftime(data, 100, "%d.%m.%Y", localtime(&now));

		string dataCurenta = string(data);
		string ziEv = dataEv.substr(0, 2);
		string lunaEv = dataEv.substr(3, 2);
		string anEv = dataEv.substr(6, 4);
		string ziCurenta = dataCurenta.substr(0, 2);
		string lunaCurenta = dataCurenta.substr(3, 2);
		string anCurent = dataCurenta.substr(6, 4);

		if (anEv > anCurent) {
			return true;
		}
		else if (anEv == anCurent) {
			if (lunaEv > lunaCurenta) {
				return true;
			}
			else if (lunaEv == lunaCurenta) {
				if (ziEv > ziCurenta) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}

	 }

	  string Utils::toLowerCase(string cuvant) {
		  string cuvantLower;
		  for (int i = 0; i < cuvant.length(); i++)
		  {
			  cuvantLower += tolower(cuvant[i]);
		  }
		  return cuvantLower;
	  }

