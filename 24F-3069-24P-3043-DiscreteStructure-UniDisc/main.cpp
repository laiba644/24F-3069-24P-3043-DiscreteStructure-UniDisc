#include <iostream>
#include <string>
#include "UniversityDatabase.h"
#include "CourseScheduling.h"
#include "RelationsModule.h"
#include "ConsistencyChecker.h"
#include "InductionChecker.h"
#include "EfficiencyBenchmark.h"
#include "UnidiscUtils.h"
using namespace std;
//  DISPLAY HELPERS 
void showAllStudents(UniversityDatabase& db) {
    printTitle("STUDENTS");
    if (db.studentCount == 0)
        cout << "(No students added yet)\n";
    else
        for (int i = 0; i < db.studentCount; i++)
            cout << (i + 1) << ". " << db.students[i] << "\n";
}

void mainMenu()
{
    printTitle("UNIDISC ENGINE - (LAIBA MODULES)");
    cout << "1) Student & Course Management\n";
    cout << "2) Course Scheduling\n";
    cout << "3) Induction Checker\n";
    cout << "4) Relations Module\n";
    cout << "5) Consistency Checker\n";
    cout << "6) Algorithm Efficiency Benchmarks\n";
    cout << "0) Exit\n\n";
    cout << "Enter choice: ";
}

void handleStudentCourse(UniversityDatabase& db)
{
    while (true)
    {
        printTitle("STUDENT & COURSE MANAGEMENT");
        cout << "1) Add Student\n";
        cout << "2) Add Course\n";
        cout << "3) Add Prerequisite\n";
        cout << "4) Register Student in Course\n";
        cout << "5) Show All Students\n";
        cout << "6) Show All Courses\n";
        cout << "0) Back\n\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        string name;
        string code;
        string prereq;
        int credit;
        int sem;

        switch (ch)
        {
        case 1:
            cout << "Enter Student Name: ";
            getline(cin, name);
            db.addStudent(name);
            break;

        case 2:
            cout << "Enter Course Code: ";
            getline(cin, code);
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Credits: ";
            cin >> credit;
            clearInput();
            cout << "Semester: ";
            cin >> sem;
            clearInput();
            db.addCourse(code, name, credit, sem);
            break;

        case 3:
            cout << "Course Code: ";
            getline(cin, code);
            cout << "Prerequisite Code: ";
            getline(cin, prereq);
            db.addCoursePrerequisite(code, prereq);
            break;

        case 4:
            cout << "Student Name: ";
            getline(cin, name);
            cout << "Course Code: ";
            getline(cin, code);
            db.registerStudentCourse(name, code);
            break;

        case 5:
            db.showAllStudents();
            break;

        case 6:
            db.showAllCourses();
            break;

        default:
            cout << "Invalid Option.\n";
        }

        pauseConsole();
    }
}

void handleScheduling(UniversityDatabase& db, CourseScheduling& sch)
{
    while (true)
    {
        printTitle("COURSE SCHEDULING");
        cout << "1) Import Courses from DB\n";
        cout << "2) Load Courses from File\n";
        cout << "3) Display Semester-wise Courses\n";
        cout << "4) Generate Valid Semester Plan\n";
        cout << "0) Back\n\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        switch (ch)
        {
        case 1:
            sch.importCoursesFromDB(db);
            break;

        case 2:
            sch.loadCoursesFromFile("courses.txt");
            break;

        case 3:
            sch.displayCourses();
            break;

        case 4:
            sch.generateValidSemesterPlan();
            break;

        default:
            cout << "Invalid Option.\n";
        }

        pauseConsole();
    }
}

void handleInduction(InductionChecker& ind)
{
    while (true)
    {
        printTitle("INDUCTION CHECKER");
        cout << "1) Get Full Prerequisite Chain\n";
        cout << "2) Verify Student Eligibility\n";
        cout << "0) Back\n\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        string course;

        switch (ch)
        {
        case 1:
            cout << "Enter Course Code: ";
            getline(cin, course);
            ind.printFullChain(course);
            break;

        case 2:
            ind.verifyStudentEligibility();
            break;

        default:
            cout << "Invalid Option.\n";
        }

        pauseConsole();
    }
}

void handleRelations(RelationsModule& rel)
{
    while (true)
    {
        printTitle("RELATIONS MODULE");
        cout << "1) Add Student-Course Pair\n";
        cout << "2) Add Faculty-Course Pair\n";
        cout << "3) Show All Relations\n";
        cout << "0) Back\n\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        string s;
        string c;
        string f;

        switch (ch)
        {
        case 1:
            cout << "Student: ";
            getline(cin, s);
            cout << "Course: ";
            getline(cin, c);
            rel.addStudentCoursePair(s, c);
            break;

        case 2:
            cout << "Faculty: ";
            getline(cin, f);
            cout << "Course: ";
            getline(cin, c);
            rel.addFacultyCoursePair(f, c);
            break;

        case 3:
            rel.showAllRelations();
            break;

        default:
            cout << "Invalid Option.\n";
        }

        pauseConsole();
    }
}

void handleConsistency(ConsistencyChecker& chk)
{
    while (true)
    {
        printTitle("CONSISTENCY CHECKER");
        cout << "1) Check Missing Prerequisites\n";
        cout << "2) Check Course Overlaps\n";
        cout << "3) Run All Checks\n";
        cout << "0) Back\n\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        switch (ch)
        {
        case 1:
            chk.checkMissingPrerequisites();
            break;

        case 2:
            chk.checkCourseOverlaps();
            break;

        case 3:
            chk.runAllChecks();
            break;

        default:
            cout << "Invalid Option.\n";
        }

        pauseConsole();
    }
}

void handleEfficiency(EfficiencyBenchmark& bench)
{
    while (true)
    {
        printTitle("EFFICIENCY BENCHMARKS");
        cout << "1) Benchmark Prerequisite Chains\n";
        cout << "0) Back\n\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        if (ch == 1)
            bench.benchmarkPrerequisiteChains();
        else
            cout << "Invalid Option.\n";

        pauseConsole();
    }
}

int main()
{
    UniversityDatabase db;
    CourseScheduling sch;
    InductionChecker ind(&sch);
    RelationsModule rel(&db);
    ConsistencyChecker chk(&sch, &ind, &rel);
    EfficiencyBenchmark bench(&sch, &ind);

    while (true)
    {
        mainMenu();
        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0)
            break;

        switch (ch)
        {
        case 1:
            handleStudentCourse(db);
            break;

        case 2:
            handleScheduling(db, sch);
            break;

        case 3:
            handleInduction(ind);
            break;

        case 4:
            handleRelations(rel);
            break;

        case 5:
            handleConsistency(chk);
            break;

        case 6:
            handleEfficiency(bench);
            break;

        default:
            cout << "Invalid option.\n";
        }
    }

    cout << "\nExiting UNIDISC Engine. BYE BYE!\n";
    return 0;
}
