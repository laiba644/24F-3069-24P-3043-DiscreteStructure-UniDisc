#include "UnidiscUtils.h"
#include <iostream>
using namespace std;

string toUpper(const string& s) {
    string res = s;
    for (char& c : res)
        if (c >= 'a' && c <= 'z')
            c -= 32;
    return res;
}

string trim(const string& s) {
    int left = 0;
    while (left < (int)s.size() && s[left] == ' ')
        left++;

    int right = s.size() - 1;
    while (right >= 0 && s[right] == ' ')
        right--;

    if (left > right) return "";
    return s.substr(left, right - left + 1);
}

//  INPUT UTILS 
void clearInput() {
    cin.clear();
    while (cin.peek() != '\n' && cin.peek() != EOF)  // stop at newline or end
        cin.get();
    if (cin.peek() == '\n') cin.get();               // finally remove newline
}


int safeIntInput(int minVal, int maxVal) {
    int x;
    while (true) {
        if (cin >> x && x >= minVal && x <= maxVal) {
            clearInput();
            return x;
        }
        cout << "Enter a valid number between " << minVal
            << " and " << maxVal << ": ";
        clearInput();
    }
}

//  DISPLAY UTILS 
void pauseConsole() {
    cout << endl << "Press Enter to continue...";
    cin.ignore();
}

void printTitle(const string& text) {
    cout << endl << "===== " << text << " =====" << endl;
}
