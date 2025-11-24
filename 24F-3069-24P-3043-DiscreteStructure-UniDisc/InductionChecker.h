#ifndef INDUCTIONCHECKER_H
#define INDUCTIONCHECKER_H
#include <string>
using namespace std;
class CourseScheduling;
class InductionChecker {
private:
    CourseScheduling* sys;   // pointer to Scheduling Module
    void dfsAll(int index, bool visited[]);
    string up(const string& s) {
        string r = s;
        for (char& c : r) if (c >= 'a' && c <= 'z') c -= 32;
        return r;
    }

public:
    InductionChecker(CourseScheduling* ptr);

    void getFullChain(const string& course,
        string chain[], int& chainCount);

    bool verifyEligibility(const string& targetCourse,
        string completed[], int completedCount);
};

#endif
