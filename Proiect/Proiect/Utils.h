#pragma once
#include <iostream>
using namespace std;

class Utils {
public:
	static bool isNumber(string nrString);
	static bool hasOnlyLetters(string s);
	static bool isValidDate(string data);
	static bool isValidHour(string s);
	static bool esteDataInViitor(string dataEv);
};