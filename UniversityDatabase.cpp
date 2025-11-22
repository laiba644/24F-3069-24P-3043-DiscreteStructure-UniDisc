#include "UniversityDatabase.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#include <algorithm>  

string toUpper(const string& s) {
    string res = s;
    for (char& c : res)
        if (c >= 'a' && c <= 'z')
            c -= 32;
    return res;
}


UniversityDatabase::UniversityDatabase() {
    // STUDENTS
    studentCount = 0;
    studentCap = 50;
    students = new string[studentCap];
    studentCourses = new string * [studentCap];
    courseCountOfStudent = new int[studentCap];
    for (int i = 0; i < studentCap; i++) {
        studentCourses[i] = new string[10]; // max 6 courses realistically
        courseCountOfStudent[i] = 0;
    }

    // COURSES
    courseCount = 0;
    courseCap = 200;
    courseCodes = new string[courseCap];
    courseNames = new string[courseCap];
    courseCredits = new int[courseCap];
    courseSemester = new int[courseCap];

    prereqCount = new int[courseCap];
    coursePrerequisites = new string * [courseCap];
    for (int i = 0; i < courseCap; i++) {
        prereqCount[i] = 0;
        coursePrerequisites[i] = new string[15]; // up to 19 allowed, but 15 safe
    }

    // FACULTY & ROOMS
    facultyCount = 0;
    facultyCap = 50;
    faculty = new string[facultyCap];

    roomCount = 0;
    roomCap = 50;
    rooms = new string[roomCap];
}

UniversityDatabase::~UniversityDatabase() {
    delete[] students;
    delete[] courseCodes;
    delete[] courseNames;
    delete[] courseCredits;
    delete[] courseSemester;
    delete[] prereqCount;
    delete[] faculty;
    delete[] rooms;

    for (int i = 0; i < studentCap; i++)
        delete[] studentCourses[i];
    delete[] studentCourses;
    delete[] courseCountOfStudent;

    for (int i = 0; i < courseCap; i++)
        delete[] coursePrerequisites[i];
    delete[] coursePrerequisites;
}

// ---------------- STUDENTS ----------------
void UniversityDatabase::addStudent(string name) {
    if (studentCount >= studentCap) return;
    students[studentCount++] = name;
}

int UniversityDatabase::getStudentIndex(string name) {
    for (int i = 0; i < studentCount; i++)
        if (students[i] == name) return i;
    return -1;
}

// ---------------- COURSES ----------------
void UniversityDatabase::addCourse(string code, string name, int credit, int sem) {
    code = toUpper(code);
    courseCodes[courseCount] = code;
    courseNames[courseCount] = name;
    courseCredits[courseCount] = credit;
    courseSemester[courseCount] = sem;
    courseCount++;
}

int UniversityDatabase::getCourseIndex(string code) {
    for (int i = 0; i < courseCount; i++)
        if (courseCodes[i] == code) return i;
    return -1;
}

void UniversityDatabase::addCoursePrerequisite(string course, string prereq) {
    course = toUpper(course);
    int i = getCourseIndex(course);
    int j = getCourseIndex(prereq);
    if (i == -1 || j == -1) 
        return;
    coursePrerequisites[i][prereqCount[i]++] = prereq;
}

// ---------------- REGISTRATION ----------------
void UniversityDatabase::registerStudentCourse(string student, string course) {
    course = toUpper(course);
    int s = getStudentIndex(student);
    int c = getCourseIndex(course);
    if (s == -1 || c == -1) return;
    studentCourses[s][courseCountOfStudent[s]++] = course;
}

// ---------------- LOADING FILES ----------------
void UniversityDatabase::loadCoursesFromFile(string f1, string f2) {
    // Load course main data
    ifstream file(f1);
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string code, name, cred, sem;
        stringstream ss(line);
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, cred, ',');
        getline(ss, sem, ',');
        addCourse(code, name, stoi(cred), stoi(sem));
    }
    file.close();

    // Load prerequisites
    ifstream file2(f2);
    while (getline(file2, line)) {
        if (line.empty()) continue;
        string course, prereq;
        stringstream ss(line);
        getline(ss, course, ',');
        getline(ss, prereq, ',');
        addCoursePrerequisite(course, prereq);
    }
    file2.close();
}
// ====================== FACULTY / LAB QUERIES =======================

// Placeholder: faculty-course mapping will be provided by FunctionsModule or LogicEngine.
// DB does not decide the assignment. So we return "" (unknown) if no module sets it.
string UniversityDatabase::getFacultyOfCourse(const string& courseCode) const {
    // we only normalize and validate
    string code = toUpper(courseCode);
    int idx = -1;
    for (int i = 0; i < courseCount; i++) {
        if (courseCodes[i] == code) {
            idx = i;
            break;
        }
    }
    // If course exists but DB does not maintain faculty mapping,
    // we return empty string. Other modules will interpret it.
    if (idx == -1)
        return "";
    return "";
}

// Placeholder: lab-course mapping not stored in DB, used only via LogicEngine.
string UniversityDatabase::getLabOfCourse(const string& courseCode) const {
    string code = toUpper(courseCode);
    int idx = -1;
    for (int i = 0; i < courseCount; i++) {
        if (courseCodes[i] == code) {
            idx = i;
            break;
        }
    }
    if (idx == -1)
        return "";
    return "";
}

