#ifndef CONSISTENCY_CHECKER_H
#define CONSISTENCY_CHECKER_H

#include "CourseScheduling.h"
#include "InductionChecker.h"
#include "RelationsModule.h"
#include "FunctionsModule.h"
#include "UniversityDatabase.h"
using namespace std;

class ConsistencyChecker {
private:
    CourseScheduling* sys;
    InductionChecker* indu;
    RelationsModule* rel;
    FunctionsModule* func;
    UniversityDatabase* db;

public:
    ConsistencyChecker(CourseScheduling*, InductionChecker*, RelationsModule*, FunctionsModule*, UniversityDatabase*);

    void checkMissingPrerequisites();
    void checkCourseOverlaps();
    void checkStudentOverload(int limit);
    void runAllChecks();
};

#endif