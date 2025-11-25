#ifndef COMBINATIONMODULE_H
#define COMBINATIONMODULE_H
#include <iostream>
#include <string>
#include "UniversityDatabase.h"
using namespace std;

class CombinationModule {
public:
    CombinationModule();
    ~CombinationModule();

    long long factorial(int n);
    long long nCr(int n, int r);

    void generateProjectGroups(int groupSize, UniversityDatabase& db);
    void assignLabSessions(int studentsPerLab, UniversityDatabase& db);
    void displayCombinationStats(UniversityDatabase& db);
};

#endif
