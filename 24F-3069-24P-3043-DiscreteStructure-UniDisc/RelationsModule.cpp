#include "RelationsModule.h"
#include "UniversityDatabase.h"
#include <iostream>
using namespace std;

RelationsModule::RelationsModule(UniversityDatabase* dbPtr) {
    db = dbPtr;
    initMatrices();
}

void RelationsModule::attachDatabase(UniversityDatabase* dbPtr) {
    db = dbPtr;
}

void RelationsModule::initMatrices() {
    studentCourse = new int* [MAX_STUDENTS];
    facultyCourse = new int* [MAX_FACULTY];
    courseRoom = new int* [MAX_COURSES];
    courseConflict = new int* [MAX_COURSES];

    for (int i = 0; i < MAX_STUDENTS; i++)
        studentCourse[i] = new int[MAX_COURSES];

    for (int i = 0; i < MAX_FACULTY; i++)
        facultyCourse[i] = new int[MAX_COURSES];

    for (int i = 0; i < MAX_COURSES; i++) {
        courseRoom[i] = new int[MAX_ROOMS];
        courseConflict[i] = new int[MAX_COURSES];
    }

    clearMatrix(studentCourse, MAX_STUDENTS, MAX_COURSES);
    clearMatrix(facultyCourse, MAX_FACULTY, MAX_COURSES);
    clearMatrix(courseRoom, MAX_COURSES, MAX_ROOMS);
    clearMatrix(courseConflict, MAX_COURSES, MAX_COURSES);
}

void RelationsModule::clearMatrix(int** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = 0;
}

RelationsModule::~RelationsModule() {
    for (int i = 0; i < MAX_STUDENTS; i++) delete[] studentCourse[i];
    delete[] studentCourse;

    for (int i = 0; i < MAX_FACULTY; i++) delete[] facultyCourse[i];
    delete[] facultyCourse;

    for (int i = 0; i < MAX_COURSES; i++) {
        delete[] courseRoom[i];
        delete[] courseConflict[i];
    }
    delete[] courseRoom;
    delete[] courseConflict;
}

// ============ RELATION BUILDING FROM DB DATA ============
void RelationsModule::addStudentCoursePair(const string& studentName, const string& courseCode) {
    if (!db) return;
    int s = db->getStudentIndex(studentName);
    int c = db->getCourseIndex(courseCode);
    if (s == -1 || c == -1) return;
    studentCourse[s][c] = 1;
}

void RelationsModule::addFacultyCoursePair(const string& facultyName, const string& courseCode) {
    if (!db) return;
    for (int i = 0;i < db->facultyCount;i++) {
        if (db->faculty[i] == facultyName) {
            int c = db->getCourseIndex(courseCode);
            if (c != -1)
                facultyCourse[i][c] = 1;
        }
    }
}

void RelationsModule::addCourseRoomPair(const string& courseCode, const string& roomName) {
    if (!db) return;
    int ci = db->getCourseIndex(courseCode);
    for (int r = 0;r < db->roomCount;r++) {
        if (db->rooms[r] == roomName) {
            courseRoom[ci][r] = 1;
        }
    }
}

void RelationsModule::addCourseConflictPair(const string& c1, const string& c2) {
    if (!db) return;
    int i1 = db->getCourseIndex(c1);
    int i2 = db->getCourseIndex(c2);
    if (i1 == -1 || i2 == -1) return;
    courseConflict[i1][i2] = 1;
    courseConflict[i2][i1] = 1;
}

bool RelationsModule::isCourseConflict(const string& c1, const string& c2) const {
    if (!db) return false;
    int i = db->getCourseIndex(c1);
    int j = db->getCourseIndex(c2);
    if (i == -1 || j == -1) return false;
    return courseConflict[i][j] == 1;
}

// ============= DISPLAY RELATIONS ==============
void RelationsModule::showStudentCourseRelation() {
    if (!db) return;
    cout << "\n STUDENT → COURSE RELATION \n    ";
    for (int j = 0;j < db->courseCount;j++) cout << db->courseCodes[j] << " ";
    cout << "\n";

    for (int i = 0;i < db->studentCount;i++) {
        cout << db->students[i] << " : ";
        for (int j = 0;j < db->courseCount;j++)
            cout << studentCourse[i][j] << " ";
        cout << "\n";
    }
}

void RelationsModule::showCourseConflictRelation() {
    if (!db) return;
    cout << "\n COURSE CONFLICT GRAPH \n    ";
    for (int j = 0;j < db->courseCount;j++) cout << db->courseCodes[j] << " ";
    cout << "\n";

    for (int i = 0;i < db->courseCount;i++) {
        cout << db->courseCodes[i] << " : ";
        for (int j = 0;j < db->courseCount;j++)
            cout << courseConflict[i][j] << " ";
        cout << "\n";
    }
}

// ========= RELATION PROPERTY ANALYSIS ============
bool RelationsModule::isReflexive(int** rel, int n) const {
    for (int i = 0;i < n;i++)
        if (rel[i][i] == 0) return false;
    return true;
}

bool RelationsModule::isSymmetric(int** rel, int n) const {
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            if (rel[i][j] == 1 && rel[j][i] == 0) return false;
    return true;
}

bool RelationsModule::isTransitive(int** rel, int n) const {
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            if (rel[i][j] == 1)
                for (int k = 0;k < n;k++)
                    if (rel[j][k] == 1 && rel[i][k] == 0) return false;
    return true;
}

bool RelationsModule::isAntisymmetric(int** rel, int n) const {
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            if (i != j && rel[i][j] == 1 && rel[j][i] == 1) return false;
    return true;
}

void RelationsModule::analyzeCourseConflictRelation() {
    if (!db) return;
    cout << "\nCOURSE CONFLICT PROPERTIES\n";
    bool refl = isReflexive(courseConflict, db->courseCount);
    bool symm = isSymmetric(courseConflict, db->courseCount);
    bool trans = isTransitive(courseConflict, db->courseCount);
    bool anti = isAntisymmetric(courseConflict, db->courseCount);

    cout << "\nReflexive? " << (refl ? "Yes" : "No");
    cout << "\nSymmetric? " << (symm ? "Yes" : "No");
    cout << "\nTransitive? " << (trans ? "Yes" : "No");
    cout << "\nAntisymmetric? " << (anti ? "Yes" : "No");
    cout << "\nEquivalence Relation? " << ((refl && symm && trans) ? "Yes" : "No");
    cout << "\nPartial Order? " << ((refl && anti && trans) ? "Yes" : "No") << "\n";
}

// ========= INDIRECT STUDENT CONFLICT DETECTION ============
void RelationsModule::detectIndirectStudentConflicts() {
    if (!db) return;
    cout << "\nINDIRECT STUDENT CONFLICTS\n";

    bool any = false;
    for (int s = 0;s < db->studentCount;s++) {
        bool found = false;
        for (int c1 = 0;c1 < db->courseCount;c1++) {
            if (studentCourse[s][c1] == 1) {
                for (int c2 = 0;c2 < db->courseCount;c2++) {
                    if (studentCourse[s][c2] == 1 && courseConflict[c1][c2] == 1) {
                        cout << "⚠ Student " << db->students[s]
                            << " has conflicting courses: "
                            << db->courseCodes[c1] << " and "
                            << db->courseCodes[c2] << "\n";
                        any = true;
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
        }
        if (!found) cout << "✓ Student " << db->students[s] << ": No conflicts.\n";
    }

    if (!any) cout << "\nNo indirect conflicts found.\n";
}
