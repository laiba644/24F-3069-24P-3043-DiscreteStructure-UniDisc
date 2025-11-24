#include "ConsistencyChecker.h"
#include <iostream>
using namespace std;

ConsistencyChecker::ConsistencyChecker(CourseScheduling* s, InductionChecker* i,
    RelationsModule* r, FunctionsModule* f, UniversityDatabase* d) {
    sys = s; indu = i; rel = r; func = f; db = d;
}

void ConsistencyChecker::checkMissingPrerequisites() {
    cout << "\n CHECK: Missing Prerequisites \n";

    for (int s = 0; s < db->studentCount; s++) {
        string student = db->students[s];

        // collect all courses taken by this student
        string completed[10];
        int cnt = db->courseCountOfStudent[s];
        for (int i = 0; i < cnt; i++)
            completed[i] = db->studentCourses[s][i];

        for (int i = 0; i < cnt; i++) {
            if (!indu->verifyEligibility(completed[i], completed, cnt)) {
                cout << " Violation | Student: " << student
                    << " | Missing prerequisites for " << completed[i] << "\n";
            }
        }
    }
}

void ConsistencyChecker::checkCourseOverlaps() {
    cout << "\n CHECK: Timetable / Course Conflict \n";

    for (int s = 0; s < db->studentCount; s++) {
        string student = db->students[s];
        int cnt = db->courseCountOfStudent[s];

        for (int i = 0; i < cnt; i++) {
            for (int j = i + 1; j < cnt; j++) {
                string c1 = db->studentCourses[s][i];
                string c2 = db->studentCourses[s][j];

                if (rel->isCourseConflict(c1, c2)) {
                    cout << " Clash for " << student << ": " << c1 << " <-> " << c2 << "\n";
                }
            }
        }
    }
}

void ConsistencyChecker::checkStudentOverload(int limit) {
    cout << "\n CHECK: Student Course Overload \n";

    for (int s = 0; s < db->studentCount; s++) {
        if (db->courseCountOfStudent[s] > limit) {
            cout << "Overload | " << db->students[s]
                << " taking " << db->courseCountOfStudent[s] << " courses\n";
        }
    }
}

void ConsistencyChecker::runAllChecks() {
    checkMissingPrerequisites();
    checkCourseOverlaps();
    checkStudentOverload(5);
}
