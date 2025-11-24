#ifndef PROOFVERIFIER_H
#define PROOFVERIFIER_H


#include "CourseScheduling.h"
#include "InductionChecker.h"
#include "LogicEngine.h"
#include "UniversityDatabase.h"
#include <string>
using namespace std;

class ProofVerifier {
private:
    CourseScheduling* sys;
    InductionChecker* indu;
    LogicEngine* logic;
    UniversityDatabase* db;

    void sortChain(string arr[], int n); // NEW

public:
    ProofVerifier(CourseScheduling*, InductionChecker*, LogicEngine*, UniversityDatabase*);

    void proveCourseEligibility(const string& course, string completed[], int cCount);
    void proveLogicRule(int ruleIndex);
    void proveFacultyLabConsistency(const string& course);
};

#endif