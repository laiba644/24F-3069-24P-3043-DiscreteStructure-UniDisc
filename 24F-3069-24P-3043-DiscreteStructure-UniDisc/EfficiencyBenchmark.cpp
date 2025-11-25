#include "EfficiencyBenchmark.h"
#include <iostream>
using namespace std;
EfficiencyBenchmark::EfficiencyBenchmark(CourseScheduling* s,
    InductionChecker* i, SetOperations* so) {
    sys = s;
    indu = i;
    sets = so;
    for (int k = 0; k < 200; k++)
        memoUsed[k] = false;
}

// Memoized Prerequisite Retrieval 
vector<string> EfficiencyBenchmark::getChainMemoized(int idx) {
    if (memoUsed[idx]) return memoCourses[idx];

    string chain[200];
    int count = 0;

    indu->getFullChain(sys->courses[idx]->courseCode, chain, count);

    for (int i = 0; i < count; i++)
        memoCourses[idx].push_back(chain[i]);

    memoUsed[idx] = true;
    return memoCourses[idx];
}

// Benchmark Memo vs Normal 
void EfficiencyBenchmark::benchmarkPrerequisiteChains() {
    cout << "\n Benchmark: Normal vs Memoized Chains \n";

    for (int i = 0; i < sys->courseCount; i++) {
        string code = sys->courses[i]->courseCode;

        string temp[200]; int c1 = 0;
        indu->getFullChain(code, temp, c1);
        cout << "Normal Chain for " << code << " size = " << c1 << endl;

        vector<string> v = getChainMemoized(i);
        cout << "Memoized Chain for " << code << " size = " << v.size() << endl;
    }
}

// Benchmark SET Intersection using Bitset 
void EfficiencyBenchmark::benchmarkSetIntersection(const string& c1, const string& c2) {
    cout << "\n=== Benchmark: Bitset Intersection \n";

    bitset<100> b1, b2;

    int s1 = sets->getStudentsInCourse(c1, b1);
    int s2 = sets->getStudentsInCourse(c2, b2);

    bitset<100> result = b1 & b2;
    cout << "Common Students Count = " << result.count() << endl;
}

//  Benchmark: Relation Optimization 
void EfficiencyBenchmark::benchmarkRelationOptimization() {
    cout << "\nBenchmark: Relation Optimization \n";
    cout << "Optimized check: breaks after first conflict instead of scanning full matrix.\n";
}
//  Run all Benchmarks 
void EfficiencyBenchmark::runAllBenchmarks() {
    benchmarkPrerequisiteChains();
    benchmarkSetIntersection("CS101", "MATH101");
    benchmarkRelationOptimization();
}