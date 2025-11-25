#include "CombinationModule.h"
#include <iostream>
using namespace std;

CombinationModule::CombinationModule() {}
CombinationModule::~CombinationModule() {}

long long CombinationModule::factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

long long CombinationModule::nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// GROUP GENERATION 
void CombinationModule::generateProjectGroups(int groupSize, UniversityDatabase& db) {
    int studentCount = db.studentCount;
    string* students = db.students;

    cout << "\n========================================";
    cout << "\n    PROJECT GROUPS (Size: " << groupSize << ")";
    cout << "\n========================================\n";

    if (groupSize <= 0 || groupSize > studentCount) {
        cout << "Invalid group size.\n";
        return;
    }

    long long totalGroups = nCr(studentCount, groupSize);
    cout << "Total possible groups: " << totalGroups << "\n\n";

    int* combo = new int[groupSize];
    for (int i = 0; i < groupSize; i++) combo[i] = i;

    long long count = 0;
    while (true) {
        cout << "Group " << (count + 1) << ": ";
        for (int i = 0; i < groupSize; i++) {
            cout << students[combo[i]];
            if (i < groupSize - 1) cout << ", ";
        }
        cout << "\n";
        count++;

        int i;
        for (i = groupSize - 1; i >= 0; i--)
            if (combo[i] != i + studentCount - groupSize) break;
        if (i < 0) break;

        combo[i]++;
        for (int j = i + 1; j < groupSize; j++)
            combo[j] = combo[j - 1] + 1;
    }

    delete[] combo;
    cout << "\n" << count << " groups generated successfully.\n";
}

// LAB SESSIONS
void CombinationModule::assignLabSessions(int studentsPerLab, UniversityDatabase& db) {
    int studentCount = db.studentCount;
    string* students = db.students;

    cout << "\n========================================";
    cout << "\n      LAB SESSION ASSIGNMENT";
    cout << "\n========================================\n";

    if (studentsPerLab <= 0 || studentCount == 0) {
        cout << "Invalid parameters.\n";
        return;
    }

    int totalLabs = (studentCount + studentsPerLab - 1) / studentsPerLab;

    for (int lab = 0; lab < totalLabs; lab++) {
        cout << "\n--- Lab Session " << (lab + 1) << " ---\n";
        int start = lab * studentsPerLab;
        int end = start + studentsPerLab;
        if (end > studentCount) end = studentCount;

        for (int i = start; i < end; i++)
            cout << "  " << students[i] << "\n";
    }
}

// STATS
void CombinationModule::displayCombinationStats(UniversityDatabase& db) {
    int studentCount = db.studentCount;
    if (studentCount == 0) {
        cout << "No students available.\n";
        return;
    }
    cout << "\n========================================";
    cout << "\n    COMBINATION STATISTICS";
    cout << "\n========================================\n";

    cout << "Total Students: " << studentCount << "\n\n";
    for (int r = 1; r <= studentCount && r <= 10; r++)
        cout << "C(" << studentCount << "," << r << ") = " << nCr(studentCount, r) << "\n";
}
