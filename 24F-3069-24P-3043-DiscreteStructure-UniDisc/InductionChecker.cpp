#include "InductionChecker.h"
#include "CourseScheduling.h"
#include <iostream>
using namespace std;
InductionChecker::InductionChecker(CourseScheduling* ptr) {
    sys = ptr;
}

void InductionChecker::dfsAll(int index, bool visited[]) {
    visited[index] = true;
    for (int j = 0; j < sys->courseCount; j++) {
        if (sys->prerequisiteMatrix[index][j] == 1 && !visited[j]) {
            dfsAll(j, visited);
        }
    }
}
void InductionChecker::getFullChain(const string& course,
    string chain[], int& chainCount) {
    string up = this->up(course);
    int idx = sys->getCourseIndex(up);

    if (idx == -1) {
        cout << "Course not found.\n";
        return;
    }

    bool* visited = new bool[sys->courseCount];
    for (int i = 0; i < sys->courseCount; i++)
        visited[i] = false;

    dfsAll(idx, visited);

    chainCount = 0;
    for (int i = 0; i < sys->courseCount; i++) {
        if (visited[i] && sys->courses[i]->courseCode != up) {
            chain[chainCount++] = sys->courses[i]->courseCode;
        }
    }

    delete[] visited;
}

bool InductionChecker::verifyEligibility(const string& targetCourse,string completed[], int completedCount) {
    string target = up(targetCourse);
    //added if 0 prerequisities and then it will alwasy be eligible
    if (completedCount == 0) {
        // Check if course even has prerequisites
        string chain[200];
        int chainCount = 0;
        getFullChain(target, chain, chainCount);

        if (chainCount == 0)
            return true;   // No prerequisites -> Eligible
        else
            return false;  // Has prerequisites -> Not eligible
    }
    // Convert completed to uppercase
    for (int i = 0; i < completedCount; i++)
        completed[i] = up(completed[i]);

    // Get full prerequisite chain
    string chain[200];
    int chainCount = 0;
    getFullChain(target, chain, chainCount);

    // Check if every course in chain is completed
    for (int i = 0; i < chainCount; i++) {
        bool ok = false;
        for (int j = 0; j < completedCount; j++) {
            if (chain[i] == completed[j]) 
                ok = true;
        }
        if (!ok)
            return false;
    }
    return true;
}
