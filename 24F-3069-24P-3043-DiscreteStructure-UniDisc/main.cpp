#include <iostream>
#include <string>
#include "UniversityDatabase.h"
#include "CourseScheduling.h"
#include "CombinationModule.h"
#include "InductionChecker.h"
#include "LogicEngine.h"
#include "SetOperations.h"
#include "RelationsModule.h"
#include "FunctionsModule.h"
#include "ProofVerifier.h"
#include "ConsistencyChecker.h"
#include "EfficiencyBenchmark.h"
#include "UnidiscUtils.h"
using namespace std;
//  MAIN MENU
void mainMenu() {
    printTitle("UNIDISC ENGINE - MAIN MENU");
    cout << "1) Student & Course Management\n";
    cout << "2) Course Scheduling\n";
    cout << "3) Combination Module\n";
    cout << "4) Induction Checker\n";
    cout << "5) Logic Engine\n";
    cout << "6) Set Operations\n";
    cout << "7) Relations Module\n";
    cout << "8) Functions Module\n";
    cout << "9) Proof Module\n";
    cout << "10) Consistency Checker\n";
    cout << "11) Algorithm Efficiency Benchmarks\n";
    cout << "0) Exit\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  STUDENT-COURSE MENU 
void studentCourseMenu() {
    printTitle("STUDENT & COURSE MANAGEMENT");
    cout << "1) Add Student\n";
    cout << "2) Add Course\n";
    cout << "3) Add Course Prerequisite\n";
    cout << "4) Register Student in Course\n";
    cout << "5) Show All Students\n";
    cout << "6) Show All Courses\n";
    cout << "7) Load Courses From File\n";
    cout << "8) Add Faculty\n";
    cout << "9) Add Room\n";
	cout << "10) Assign Faculty to Course\n";
	cout << "11) Assign Lab to Course\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  SCHEDULING MENU 
void schedulingMenu() {
    printTitle("COURSE SCHEDULING MODULE");
    cout << "1) Import Courses from University DB\n";
    cout << "2) Load Courses From File\n";
    cout << "3) Load Prerequisites From File\n";
    cout << "4) Display Semester-wise Courses\n";
    cout << "5) Show Prerequisites of a Course\n";
    cout << "6) Generate Valid Semester Plan\n";
    cout << "7) Generate Valid Order For Selected Courses\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

// COMBINATION MENU 
void combinationMenu() {
    printTitle("COMBINATION MODULE");
    cout << "1) Generate Project Groups\n";
    cout << "2) Assign Lab Sessions\n";
    cout << "3) Display Combination Statistics\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  INDUCTION MENU 
void inductionMenu() {
    printTitle("INDUCTION CHECKER");
    cout << "1) Get Full Prerequisite Chain\n";
    cout << "2) Verify Student Eligibility\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

// LOGIC ENGINE MENU 
void logicEngineMenu() {
    printTitle("LOGIC ENGINE");
    cout << "1) Add Rule\n";
    cout << "2) Display Rules\n";
    cout << "3) Add Fact\n";
    cout << "4) Display Facts\n";
    cout << "5) Forward Chaining Inference\n";
    cout << "6) Verify All Rules\n";
    cout << "7) Detect Course Conflicts\n";
    cout << "8) Detect Faculty Conflicts\n";
    cout << "9) Detect Lab Conflicts\n";
    cout << "10) Load Default Rules\n";
    cout << "11) Check Tautology\n";
    cout << "12) Add Predicate\n";
    cout << "13) Display Predicates\n";
    cout << "14) Universal Quantifier\n";
    cout << "15) Existential Quantifier\n";
    cout << "16) Generate Inference Report\n";
    cout << "17) Display Knowledge Base\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  SET OPERATIONS MENU 
void setOperationsMenu() {
    printTitle("SET OPERATIONS");
    cout << "1) Create Set\n";
    cout << "2) Add Element to Set\n";
    cout << "3) Display Set\n";
    cout << "4) Display All Sets\n";
    cout << "5) Union of Two Sets\n";
    cout << "6) Intersection of Two Sets\n";
    cout << "7) Difference of Two Sets\n";
    cout << "8) Check Subset\n";
    cout << "9) Check Superset\n";
    cout << "10) Check Proper Subset\n";
    cout << "11) Check Disjoint\n";
    cout << "12) Check Equal\n";
    cout << "13) Cardinality\n";
    cout << "14) Generate Power Set\n";
    cout << "15) Cartesian Product\n";
    cout << "16) Complement\n";
    cout << "17) Students in Both Courses\n";
    cout << "18) Students in Either Course\n";
    cout << "19) Students Only in One Course\n";
    cout << "20) Common Faculties\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  RELATIONS MENU 
void relationsMenu() {
    printTitle("RELATIONS MODULE");
    cout << "1) Add Student-Course Pair\n";
    cout << "2) Add Faculty-Course Pair\n";
    cout << "3) Add Course-Room Pair\n";
    cout << "4) Add Course Conflict Pair\n";
    cout << "5) Show Student-Course Relation\n";
    cout << "6) Show Faculty-Course Relation\n";
    cout << "7) Show Course-Room Relation\n";
    cout << "8) Show Course Conflict Relation\n";
    cout << "9) Analyze Course Conflict Properties\n";
    cout << "10) Detect Indirect Student Conflicts\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  FUNCTIONS MENU 
void functionsMenu() {
    printTitle("FUNCTIONS MODULE");
    cout << "1) Map Student to Course\n";
    cout << "2) Map Course to Faculty\n";
    cout << "3) Map Faculty to Room\n";
    cout << "4) Check Injective\n";
    cout << "5) Check Surjective\n";
    cout << "6) Check Bijective\n";
    cout << "7) Inverse Course-Faculty\n";
    cout << "8) Compose Student-Faculty\n";
    cout << "9) Display All Mappings\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  PROOF MODULE MENU 
void proofMenu() {
    printTitle("PROOF MODULE");
    cout << "1) Induction Proof of Course Eligibility\n";
    cout << "2) Prove Logic Rule (by index)\n";
    cout << "3) Prove Faculty-Lab Consistency for Course\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  CONSISTENCY CHECKER MENU 
void consistencyMenu() {
    printTitle("CONSISTENCY CHECKER");
    cout << "1) Check Missing Prerequisites\n";
    cout << "2) Check Course Overlaps (Conflicts)\n";
    cout << "3) Check Student Overload\n";
    cout << "4) Run All Checks\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  EFFICIENCY BENCHMARK MENU 
void efficiencyMenu() {
    printTitle("ALGORITHM EFFICIENCY BENCHMARKS");
    cout << "1) Benchmark Prerequisite Chains (Normal vs Memoized)\n";
    cout << "2) Benchmark Set Intersection for Two Courses\n";
    cout << "3) Benchmark Relation Optimization\n";
    cout << "4) Run All Benchmarks\n";
    cout << "0) Back\n";
    cout << "\n";
    cout << "Enter choice: ";
}

//  DISPLAY HELPERS 
void showAllStudents(UniversityDatabase& db) {
    printTitle("STUDENTS");
    if (db.studentCount == 0)
        cout << "(No students added yet)\n";
    else
        for (int i = 0; i < db.studentCount; i++)
            cout << (i + 1) << ". " << db.students[i] << "\n";
}

void showAllCourses(UniversityDatabase& db) {
    printTitle("COURSES");
    if (db.courseCount == 0)
        cout << "(No courses added yet)\n";
    else {
        for (int i = 0; i < db.courseCount; i++) {
            cout << db.courseCodes[i] << " | " << db.courseNames[i]
                << " | " << db.courseCredits[i] << " CrHrs | Sem "
                << db.courseSemester[i] << "\n";
            cout << "   Prerequisites: ";
            if (db.prereqCount[i] == 0)
                cout << "None";
            else {
                for (int j = 0; j < db.prereqCount[i]; j++) {
                    cout << db.coursePrerequisites[i][j];
                    if (j < db.prereqCount[i] - 1) cout << ", ";
                }
            }
            cout << "\n";
        }
    }
}

// STUDENT & COURSE HANDLER 
void handleStudentCourse(UniversityDatabase& db) {
    while (true) {
        studentCourseMenu();
        int ch; 
        cin >> ch;
        clearInput();
        if (ch == 0)
            break;
        string name, code, prereq;
        int credit, sem;
        switch (ch) {
        case 1:
            cout << "Enter Student Name: ";
            getline(cin, name);
            db.addStudent(name);
            cout << "Student added!\n";
            break;
        case 2:
            cout << "Enter Course Code: ";
            getline(cin, code);
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Credits: "; 
            cin >> credit; 
            clearInput();
            cout << "Enter Semester: "; 
            cin >> sem; 
            clearInput();
            db.addCourse(code, name, credit, sem);
            cout << "Course added!\n";
            break;
        case 3:
            cout << "Enter Course Code: ";
            getline(cin, code);
            cout << "Enter Prerequisite Code: ";
            getline(cin, prereq);
            db.addCoursePrerequisite(code, prereq);
            cout << "Prerequisite added!\n";
            break;
        case 4:
            cout << "Enter Student Name: ";
            getline(cin, name);
            cout << "Enter Course Code: ";
            getline(cin, code);
            db.registerStudentCourse(name, code);
            cout << "Registration successful!\n";
            break;
        case 5:
            showAllStudents(db);
            break;
        case 6:
            showAllCourses(db);
            break;
        case 7:
            db.loadCoursesFromFile("courses.txt", "prerequisites.txt");
            cout << "Courses Loaded Successfully!\n";
            break;
        case 8:
            if (db.facultyCount >= db.facultyCap) {
                cout << "Faculty list full!\n";
                break;
            }
            cout << "Enter Faculty Name: ";
            getline(cin, name);
            db.faculty[db.facultyCount++] = name;
            cout << "Faculty added!\n";
            break;
        case 9:
            if (db.roomCount >= db.roomCap) {
                cout << "Room list full!\n";
                break;
            }
            cout << "Enter Room Name: ";
            getline(cin, name);
            db.rooms[db.roomCount++] = name;
            cout << "Room added!\n";
            break;
        case 10:
        {
            string facultyID, courseCode;
            cout << "Enter Faculty ID: ";
            cin >> facultyID;
            cout << "Enter Course Code: ";
            cin >> courseCode;
            db.assignFacultyToCourse(facultyID, courseCode);
            cout << "Faculty Assigned!\n";
            break;
        }
        case 11:
        {
            string labID, courseCode;
            cout << "Enter Lab Room ID: ";
            cin >> labID;
            cout << "Enter Course Code: ";
            cin >> courseCode;
            db.assignLabToCourse(labID, courseCode);
            cout << "Lab Assigned!\n";          
            break;
        }
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

//  SCHEDULING HANDLER 
void handleScheduling(UniversityDatabase& db, CourseScheduling& sch) {
    while (true) {
        schedulingMenu();
        int ch; 
        cin >> ch;
       clearInput();
        if (ch == 0)
            break;
        string code;

        switch (ch) {
        case 1:
            sch.importCoursesFromDB(db);
            cout << "Courses Imported From Database!\n";
            break;
        case 2:
            sch.loadCoursesFromFile("courses.txt");
            break;
        case 3:
            sch.loadPrerequisitesFromFile("prerequisites.txt");
            break;
        case 4:
            sch.displayCourses();
            break;
        case 5:
            cout << "Enter Course Code: "; getline(cin, code);
            sch.showPrerequisites(up(code));
            break;
        case 6:
            sch.generateValidSemesterPlan();
            break;
        case 7: {
            int n;
            cout << "How many courses? ";
            cin >> n; 
            clearInput();
            if (n <= 0) { cout << "Invalid count.\n"; 
            break;
            }
            string* arr = new string[n];
            cout << "Enter course codes:\n";
            for (int i = 0; i < n; i++) {
                cout << "Course " << (i + 1) << ": ";
                getline(cin, arr[i]);
            }
            sch.generateSubsetSequences(arr, n);
            delete[] arr;
            break;
        }
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}
//  COMBINATION HANDLER 
void handleCombination(UniversityDatabase& db, CombinationModule& comb) {
    while (true) {
        combinationMenu();
        int ch; 
        cin >> ch;
        clearInput();
        if (ch == 0) 
            break;
        int size;
        switch (ch) {
        case 1:
            cout << "Enter Group Size: ";
            cin >> size;
            clearInput();
            comb.generateProjectGroups(size, db);
            break;
        case 2:
            cout << "Enter Students Per Lab: "; 
            cin >> size;
            clearInput();
            comb.assignLabSessions(size, db);
            break;
        case 3:
            comb.displayCombinationStats(db);
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}
//  INDUCTION HANDLER
void handleInduction(CourseScheduling& sch, InductionChecker& ind) {
    while (true) {
        inductionMenu();
        int ch; 
        cin >> ch;
        clearInput();
        if (ch == 0) 
            break;
     string course;
        switch (ch) {
        case 1: {
            cout << "Enter Course Code: ";
            getline(cin, course);
            string chain[200];
            int chainCount = 0;
            ind.getFullChain(course, chain, chainCount);
            cout << "\nFull Prerequisite Chain for " << course << ":\n";
            if (chainCount == 0) {
                cout << "No prerequisites.\n";
            }
            else {
                for (int i = 0; i < chainCount; i++)
                    cout << "  " << (i + 1) << ". " << chain[i] << "\n";
            }
            break;
        }
        case 2: {
            cout << "Enter Target Course: ";
            getline(cin, course);
            int n;
            cout << "How many completed courses? "; 
            cin >> n;
            clearInput();
            if (n <= 0) {
                cout << "No completed courses provided.\n";
                break;
            }
            string* completed = new string[n];
            for (int i = 0; i < n; i++) {
                cout << "Course " << (i + 1) << ": ";
                getline(cin, completed[i]);
            }
            bool eligible = ind.verifyEligibility(course, completed, n);
            cout << "\nResult: " << (eligible ? "ELIGIBLE" : "NOT ELIGIBLE") << "\n";
            delete[] completed;

            break;
        }
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

//  LOGIC ENGINE HANDLER 

void handleLogicEngine(LogicEngine& logic) {
    while (true) {
        logicEngineMenu();
        int ch;
        cin >> ch;
        clearInput();
        if (ch == 0)
            break;

        string type, cond, concl, subject, pred, obj, name, prop;

        switch (ch) {
        case 1:

            cout << "Enter IF (subject predicate object): ";
            getline(cin, cond);
            cout << "Enter THEN (subject predicate object): ";
            getline(cin, concl);
            logic.addRule("IMPLIES", cond, concl);
            break;
        case 2:
            logic.displayRules();
            break;
        case 3:
            cout << "Fact Type: ";
            getline(cin, type);
            cout << "Subject: "; 
            getline(cin, subject);
            cout << "Predicate: ";
            getline(cin, pred);
            cout << "Object: ";
            getline(cin, obj);
            logic.addFact(type, subject, pred, obj, true);
            break;
        case 4:
            logic.displayFacts();
            break;
        case 5:
            logic.forwardChaining();
            break;
        case 6:
            logic.verifyAllRules();
            break;
        case 7:
            logic.detectCourseConflicts();
            break;
        case 8:
            logic.detectFacultyConflicts();
            break;
        case 9:
            logic.detectLabConflicts();
            break;
        case 10:
            logic.loadDefaultRules();
            break;
        case 11:
            cout << "Enter Proposition: ";
            getline(cin, prop);
            logic.isTautology(prop);
            break;
        case 12: {
            string var1, var2;
            cout << "Predicate Name: "; 
            getline(cin, name);
            cout << "Variable 1: "; 
            getline(cin, var1);
            cout << "Variable 2 (optional): ";
            getline(cin, var2);
            logic.addPredicate(name, var1, var2);
            break;
        }
        case 13:
            logic.displayPredicates();
            break;
        case 14: {
            cout << "Predicate Name: "; 
            getline(cin, name);
            int n;
            cout << "Domain Size: "; cin >> n; clearInput();
            if (n <= 0) {
                cout << "Empty domain.\n";
                break;
            }
            string* domain = new string[n];
            for (int i = 0; i < n; i++) {
                cout << "Element " << (i + 1) << ": ";
                getline(cin, domain[i]);
            }
            logic.universalQuantifier(name, domain, n);
            delete[] domain;
            break;
        }
        case 15: {
            cout << "Predicate Name: "; 
            getline(cin, name);
            int n;
            cout << "Domain Size: ";
            cin >> n; 
            clearInput();
            if (n <= 0) {
                cout << "Empty domain.\n";
                break;
            }
            string* domain = new string[n];
            for (int i = 0; i < n; i++) {
                cout << "Element " << (i + 1) << ": ";
                getline(cin, domain[i]);
            }
            logic.existentialQuantifier(name, domain, n);
            delete[] domain;
            break;
        }
        case 16:
            logic.generateInferenceReport();
            break;
        case 17:
            logic.displayKnowledgeBase();
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

// SET OPERATIONS HANDLER 
void handleSetOperations(SetOperations& setOps) {
    while (true) {
        setOperationsMenu();
        int ch;
        cin >> ch;
        clearInput();
        if (ch == 0) 
            break;
        string setName, setA, setB, element, course1, course2, dept1, dept2, universal;
        switch (ch) {
        case 1:
            cout << "Set Name: "; 
            getline(cin, setName);
            setOps.createSet(setName);
            break;
        case 2:
            cout << "Set Name: ";
            getline(cin, setName);
            cout << "Element: "; 
            getline(cin, element);
            setOps.addElementToSet(setName, element);
            break;
        case 3:
            cout << "Set Name: ";
            getline(cin, setName);
            setOps.displaySet(setName);
            break;
        case 4:
            setOps.displayAllSets();
            break;
        case 5:
            cout << "Set A: "; 
            getline(cin, setA);
            cout << "Set B: ";
            getline(cin, setB);
            {
                SetOperations::Set* result = setOps.unionSets(setA, setB);
                if (result) {
                    cout << "\nUnion:\n";
                    result->display();
                    delete result;
                }
            }
            break;
        case 6:
            cout << "Set A: ";
            getline(cin, setA);
            cout << "Set B: ";
            getline(cin, setB);
            {
                SetOperations::Set* result = setOps.intersectionSets(setA, setB);
                if (result) {
                    cout << "\nIntersection:\n";
                    result->display();
                    delete result;
                }
            }
            break;
        case 7:
            cout << "Set A: ";
            getline(cin, setA);
            cout << "Set B: ";
            getline(cin, setB);
            {
                SetOperations::Set* result = setOps.differenceSets(setA, setB);
                if (result) {
                    cout << "\nDifference (A - B):\n";
                    result->display();
                    delete result;
                }
            }
            break;
        case 8:
            cout << "Set A: ";
            getline(cin, setA);
            cout << "Set B: ";
            getline(cin, setB);
            cout << "\nIs " << setA << " subset of " << setB << "? "<< (setOps.isSubset(setA, setB) ? "Yes" : "No") << "\n";
            break;
        case 9:
            cout << "Set A: "; getline(cin, setA);
            cout << "Set B: "; getline(cin, setB);
            cout << "\nIs " << setA << " superset of " << setB << "? "<< (setOps.isSuperset(setA, setB) ? "Yes" : "No") << "\n";
            break;
        case 10:
            cout << "Set A: "; getline(cin, setA);
            cout << "Set B: "; getline(cin, setB);
            cout << "\nIs " << setA << " proper subset of " << setB << "? "<< (setOps.isProperSubset(setA, setB) ? "Yes" : "No") << "\n";
            break;
        case 11:
            cout << "Set A: "; getline(cin, setA);
            cout << "Set B: "; getline(cin, setB);
            cout << "\nAre " << setA << " and " << setB << " disjoint? " << (setOps.areDisjoint(setA, setB) ? "Yes" : "No") << "\n";
            break;
        case 12:
            cout << "Set A: "; getline(cin, setA);
            cout << "Set B: "; getline(cin, setB);
            cout << "\nAre " << setA << " and " << setB << " equal? " << (setOps.areEqual(setA, setB) ? "Yes" : "No") << "\n";
            break;
        case 13:
            cout << "Set Name: "; getline(cin, setName);
            {
                int card = setOps.cardinality(setName);
                if (card != -1)
                    cout << "\nCardinality of " << setName << " = " << card << "\n";
            }
            break;
        case 14:
            cout << "Set Name: "; getline(cin, setName);
            setOps.generatePowerSet(setName);
            break;
        case 15:
            cout << "Set A: "; getline(cin, setA);
            cout << "Set B: "; getline(cin, setB);
            setOps.cartesianProduct(setA, setB);
            break;
        case 16:
            cout << "Set Name: "; getline(cin, setName);
            cout << "Universal Set: "; getline(cin, universal);
            {
                SetOperations::Set* result = setOps.complement(setName, universal);
                if (result) {
                    cout << "\nComplement:\n";
                    result->display();
                    delete result;
                }
            }
            break;
        case 17:
            cout << "Course 1: "; 
            getline(cin, course1);
            cout << "Course 2: ";
            getline(cin, course2);
            setOps.findStudentsInBothCourses(course1, course2);
            break;
        case 18:
            cout << "Course 1: ";
            getline(cin, course1);
            cout << "Course 2: "; 
            getline(cin, course2);
            setOps.findStudentsInEitherCourse(course1, course2);
            break;
        case 19:
            cout << "Course 1: "; 
            getline(cin, course1);
            cout << "Course 2: ";
            getline(cin, course2);
            setOps.findStudentsOnlyInOneCourse(course1, course2);
            break;
        case 20:
            cout << "Department 1: "; 
            getline(cin, dept1);
            cout << "Department 2: "; 
            getline(cin, dept2);
            setOps.findCommonFaculties(dept1, dept2);
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

//  RELATIONS HANDLER 
void handleRelations(RelationsModule& rel) {
    while (true) {
        relationsMenu();
        int ch; 
        cin >> ch;
        clearInput();
        if (ch == 0) 
            break;
        string student, course, faculty, room, course1, course2;
        switch (ch) {
        case 1:
            cout << "Student Name: "; 
            getline(cin, student);
            cout << "Course Code: "; 
            getline(cin, course);
            rel.addStudentCoursePair(student, course);
            cout << "Pair added!\n";
            break;
        case 2:
            cout << "Faculty Name: "; 
            getline(cin, faculty);
            cout << "Course Code: "; 
            getline(cin, course);
            rel.addFacultyCoursePair(faculty, course);
            cout << "Pair added!\n";
            break;
        case 3:
            cout << "Course Code: ";
            getline(cin, course);
            cout << "Room Name: "; 
            getline(cin, room);
            rel.addCourseRoomPair(course, room);
            cout << "Pair added!\n";
            break;
        case 4:
            cout << "Course 1: "; 
            getline(cin, course1);
            cout << "Course 2: ";
            getline(cin, course2);
            rel.addCourseConflictPair(course1, course2);
            cout << "Conflict pair added!\n";
            break;
        case 5:
            rel.showStudentCourseRelation();
            break;
        case 6:
            rel.showFacultyCourseRelation();
            break;
        case 7:
            rel.showCourseRoomRelation();
            break;
        case 8:
            rel.showCourseConflictRelation();
            break;
        case 9:
            rel.analyzeCourseConflictRelation();
            break;
        case 10:
            rel.detectIndirectStudentConflicts();
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

// FUNCTIONS HANDLER
void handleFunctions(FunctionsModule& func) {
    while (true) {
        functionsMenu();
        int ch;
        cin >> ch;
        clearInput();
        if (ch == 0)
            break;

        switch (ch) {
        case 1:
            func.mapStudentToCourse();
            cout << "Mapping complete!\n";
            break;
        case 2:
            func.mapCourseToFaculty();
            cout << "Mapping complete!\n";
            break;
        case 3:
            func.mapFacultyToRoom();
            cout << "Mapping complete!\n";
            break;
        case 4:
            func.checkInjective();
            break;
        case 5:
            func.checkSurjective();
            break;
        case 6:
            func.checkBijective();
            break;
        case 7:
            func.inverseCourseFaculty();
            break;
        case 8:
            func.composeStudentFaculty();
            break;
        case 9:
            func.displayMappings();
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

//  PROOF MODULE HANDLER 
void handleProofModule(ProofVerifier& proof) {
    while (true) {
        proofMenu();
        int ch; 
        cin >> ch;
        clearInput();
        if (ch == 0) 
            break;

        switch (ch) {
        case 1: {
            string course;
            cout << "Enter Target Course: ";
            getline(cin, course);

            int n;
            cout << "How many completed courses? ";
            cin >> n; clearInput();
            if (n <= 0) {
                cout << "No completed courses provided.\n";
                break;
            }

            string* completed = new string[n];
            for (int i = 0; i < n; i++) {
                cout << "Course " << (i + 1) << ": ";
                getline(cin, completed[i]);
            }

            proof.proveCourseEligibility(course, completed, n);
            delete[] completed;
            break;
        }
        case 2: {
            int idx;
            cout << "Enter Rule Index (0-based, see Logic Engine module for list): ";
            cin >> idx; clearInput();
            proof.proveLogicRule(idx);
            break;
        }
        case 3: {
            string course;
            cout << "Enter Course Code: ";
            getline(cin, course);
            proof.proveFacultyLabConsistency(course);
            break;
        }
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

//  CONSISTENCY CHECKER HANDLER 
void handleConsistency(ConsistencyChecker& checker) {
    while (true) {
        consistencyMenu();
        int ch; 
        cin >> ch; 
        clearInput();
        if (ch == 0) 
            break;

        switch (ch) {
        case 1:
            checker.checkMissingPrerequisites();
            break;
        case 2:
            checker.checkCourseOverlaps();
            break;
        case 3: {
            int limit;
            cout << "Enter maximum allowed courses per student: ";
            cin >> limit;
            clearInput();
            checker.checkStudentOverload(limit);
            break;
        }
        case 4:
            checker.runAllChecks();
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}

// EFFICIENCY BENCHMARK HANDLER 
void handleEfficiency(EfficiencyBenchmark& bench) {
    while (true) {
        efficiencyMenu();
        int ch;
        cin >> ch;
        clearInput();
        if (ch == 0)
            break;

        switch (ch) {
        case 1:
            bench.benchmarkPrerequisiteChains();
            break;
        case 2: {
            string c1, c2;
            cout << "Enter first course code: ";
            getline(cin, c1);
            cout << "Enter second course code: ";
            getline(cin, c2);
            bench.benchmarkSetIntersection(c1, c2);
            break;
        }
        case 3:
            bench.benchmarkRelationOptimization();
            break;
        case 4:
            bench.runAllBenchmarks();
            break;
        default:
            cout << "Invalid Option.\n";
        }
        pauseConsole();
    }
}
int main() {
    UniversityDatabase db;
    CourseScheduling sch;
    CombinationModule comb;
    InductionChecker ind(&sch);
    LogicEngine logic(&sch);
    SetOperations setOps(&db);
    RelationsModule rel(&db);
    FunctionsModule func(&db);
    ProofVerifier proof(&sch, &ind, &logic, &db);
    ConsistencyChecker checker(&sch, &ind, &rel, &func, &db);
    EfficiencyBenchmark bench(&sch, &ind, &setOps);

    logic.setDatabase(&db);

    while (true) {
        mainMenu();
        int ch; cin >> ch; clearInput();
        if (ch == 0) break;

        switch (ch) {
        case 1:
            handleStudentCourse(db);
            break;
        case 2:
            handleScheduling(db, sch);
            break;
        case 3:
            handleCombination(db, comb);
            break;
        case 4:
            handleInduction(sch, ind);
            break;
        case 5:
            handleLogicEngine(logic);
            break;
        case 6:
            handleSetOperations(setOps);
            break;
        case 7:
            handleRelations(rel);
            break;
        case 8:
            handleFunctions(func);
            break;
        case 9:
            handleProofModule(proof);
            break;
        case 10:
            handleConsistency(checker);
            break;
        case 11:
            handleEfficiency(bench);
            break;
        default:
            cout << "Invalid option.\n";
        }
    }

    cout << "\nExiting UNIDISC Engine BYE BYE!\n";
    return 0;
}