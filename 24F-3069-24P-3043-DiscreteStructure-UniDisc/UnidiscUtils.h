#ifndef UNIDISCUTILS_H
#define UNIDISCUTILS_H

#include <string>
using namespace std;


string toUpper(const string& s);
string trim(const string& s);


void clearInput();
int safeIntInput(int minVal, int maxVal);


void pauseConsole();
void printTitle(const string& text);

#endif