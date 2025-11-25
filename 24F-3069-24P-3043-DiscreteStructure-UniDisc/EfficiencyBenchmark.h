#ifndef EFFICIENCYBENCHMARK_H
#define EFFICIENCYBENCHMARK_H

#include "CourseScheduling.h"
#include "InductionChecker.h"
#include "SetOperations.h"
#include <bitset>
#include <vector>
using namespace std;

class EfficiencyBenchmark {
private:
    CourseScheduling* sys;
    InductionChecker* indu;
    SetOperations* sets;

    vector<string> memoCourses[200]; // DP cache
    bool memoUsed[200];

    vector<string> getChainMemoized(int index);

public:
    EfficiencyBenchmark(CourseScheduling*, InductionChecker*, SetOperations*);

    void benchmarkPrerequisiteChains();
    void benchmarkSetIntersection(const string& c1, const string& c2);
    void benchmarkRelationOptimization();
    void runAllBenchmarks();
};

#endif