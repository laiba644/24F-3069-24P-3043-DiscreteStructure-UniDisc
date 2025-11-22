#ifndef UNIVERSITYDATABASE_H
#define UNIVERSITYDATABASE_H
#include <string>
using namespace std;

class UniversityDatabase {
public:
    // ---------------- STUDENT DATA ----------------
    string* students;
    int studentCount;
    int studentCap;
    string** studentCourses; // each student can take multiple courses
    int* courseCountOfStudent;

    // ---------------- COURSE DATA ----------------
    string* courseCodes;
    string* courseNames;
    int* courseCredits;
    int* courseSemester;
    int courseCount;
    int courseCap;

    // For prerequisites
    string** coursePrerequisites;
    int* prereqCount;

    // ---------------- FACULTY & ROOM DATA ----------------
    string* faculty;
    string* rooms;
    int facultyCount, facultyCap;
    int roomCount, roomCap;

public:
    UniversityDatabase();
    ~UniversityDatabase();

    // STUDENT FUNCTIONS
    void addStudent(string name);
    int getStudentIndex(string name);

    // COURSE FUNCTIONS
    void addCourse(string code, string name, int credit, int sem);
    int getCourseIndex(string code);

    void addCoursePrerequisite(string course, string prereq);

    // REGISTRATION
    void registerStudentCourse(string student, string course);

    // UTILITY
    void loadCoursesFromFile(string f1, string f2); // courses + prerequisites
};

#endif
