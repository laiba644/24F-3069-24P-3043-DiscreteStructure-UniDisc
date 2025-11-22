#ifndef UNIDISCUTILS_H
#define UNIDISCUTILS_H

#include <string>
using namespace std;

// STRING UTILS 
string toUpper(const string& s);
string trim(const string& s);

//  INPUT UTILS 
void clearInput();
int safeIntInput(int minVal, int maxVal);

//  DISPLAY UTILS 
void pauseConsole();
void printTitle(const string& text);

#endif
