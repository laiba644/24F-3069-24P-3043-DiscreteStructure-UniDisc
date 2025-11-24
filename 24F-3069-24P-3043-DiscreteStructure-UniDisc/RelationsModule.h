#ifndef RELATIONSMODULE_H
#define RELATIONSMODULE_H

#include <string>
#include <iostream>
using namespace std;

// Forward declaration to avoid circular inclusion
class UniversityDatabase;

class RelationsModule {
private:
    static const int MAX_STUDENTS = 50;
    static const int MAX_COURSES = 200;
    static const int MAX_FACULTY = 50;
    static const int MAX_ROOMS = 50;

    // CENTRAL DB LINK (only pointer, no duplicate storage)
    UniversityDatabase* db;

    // Relation Matrices
    int** studentCourse;     // Student -> Course
    int** facultyCourse;     // Faculty -> Course
    int** courseRoom;        // Course -> Room
    int** courseConflict;    // Course <-> Course Conflict Graph

private:
    void initMatrices();
    void clearMatrix(int** mat, int rows, int cols);

    // Relation property checkers
    bool isReflexive(int** rel, int n) const;
    bool isSymmetric(int** rel, int n) const;
    bool isTransitive(int** rel, int n) const;
    bool isAntisymmetric(int** rel, int n) const;

public:
    RelationsModule(UniversityDatabase* dbPtr = nullptr);
    ~RelationsModule();

    // Allow attaching DB later
    void attachDatabase(UniversityDatabase* dbPtr);

    // *** RELATION BUILDERS ***
    void addStudentCoursePair(const string& studentName, const string& courseCode);
    void addFacultyCoursePair(const string& facultyName, const string& courseCode);
    void addCourseRoomPair(const string& courseCode, const string& roomName);
    void addCourseConflictPair(const string& course1, const string& course2);

    // *** DISPLAY RELATIONS ***
    void showStudentCourseRelation();
    void showCourseConflictRelation();
    void showFacultyCourseRelation();
    void showCourseRoomRelation();

    // *** PROPERTY ANALYSIS on course conflict graph ***
    void analyzeCourseConflictRelation();

    // *** Detect indirect student conflicts ***
    void detectIndirectStudentConflicts();

    bool isCourseConflict(const string& c1, const string& c2) const;
};

#endif
