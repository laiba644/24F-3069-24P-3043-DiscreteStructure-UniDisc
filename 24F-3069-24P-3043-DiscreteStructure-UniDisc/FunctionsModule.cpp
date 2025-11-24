#include "FunctionsModule.h"
#include "UnidiscUtils.h"
#include "UniversityDatabase.h"
#include <iostream>
using namespace std;

FunctionsModule::FunctionsModule(UniversityDatabase* ptr) {
    db = ptr;
    studentToCourse = courseToFaculty = facultyToRoom = nullptr;
}

FunctionsModule::~FunctionsModule() {
    delete[] studentToCourse;
    delete[] courseToFaculty;
    delete[] facultyToRoom;
}

void FunctionsModule::attachDatabase(UniversityDatabase* ptr) {
    db = ptr;
}

// MAPPING FUNCTIONS

void FunctionsModule::mapStudentToCourse() {
    if (!db || db->studentCount == 0 || db->courseCount == 0) {
        cout << "Database empty.\n";
        return;
    }

    // free previous mapping if any
    if (studentToCourse != nullptr)
        delete[] studentToCourse;

    studentToCourse = new int[db->studentCount];

    // default: map everyone to course index 0 (safe fallback)
    for (int i = 0; i < db->studentCount; i++)
        studentToCourse[i] = 0;

    cout << "\nAssign Student -> Course (subset)\n";
    cout << "How many students do you want to assign explicitly? ";

    int n;
    cin >> n;
    clearInput();

    if (n <= 0) {
        cout << "No explicit assignments made. All students currently mapped to course index 0.\n";
        return;
    }

    if (n > db->studentCount)
        n = db->studentCount;

    
    cout << "\nAvailable students:\n";
    for (int i = 0; i < db->studentCount; i++)
        cout << "  " << i << ") " << db->students[i] << "\n";

    for (int k = 0; k < n; k++) {
        int sIdx;
        cout << "\nEnter student index #" << (k + 1) << ": ";
        cin >> sIdx;
        clearInput();

        if (sIdx < 0 || sIdx >= db->studentCount) {
            cout << "Invalid index, skipping.\n";
            continue;
        }

        cout << "Choose course index for " << db->students[sIdx] << ":\n";
        for (int c = 0; c < db->courseCount; c++)
            cout << "  " << c << ") " << db->courseCodes[c] << "\n";

        int cIdx;
        cin >> cIdx;
        clearInput();

        if (cIdx < 0 || cIdx >= db->courseCount)
            cIdx = 0;   // clamp to valid range

        studentToCourse[sIdx] = cIdx;
    }

    cout << "\nStudent-course mapping complete (selected + default).\n";
}

void FunctionsModule::mapCourseToFaculty() {
    if (db->courseCount == 0 || db->facultyCount == 0) {
        cout << "No courses or faculty available.\n";
        return;
    }

    
    if (courseToFaculty != nullptr) delete[] courseToFaculty;
    courseToFaculty = new int[db->courseCount];

    
    int n;
    cout << "How many courses would you like to assign faculty to? ";
    cin >> n;
    clearInput();

    if (n <= 0) {
        cout << "No assignments made.\n";
        return;
    }

    if (n > db->courseCount) n = db->courseCount;

    
    int* selected = new int[n];

    
    for (int i = 0; i < n; i++) {
        string code;
        cout << "Enter course code #" << (i + 1) << ": ";
        getline(cin, code);
        code = toUpper(code);

        int idx = db->getCourseIndex(code);
        if (idx == -1) {
            cout << "Invalid code. Skipping.\n";
            selected[i] = -1;
        }
        else {
            selected[i] = idx;
        }
    }

    
    for (int i = 0; i < n; i++) {
        int c = selected[i];
        if (c == -1) continue;

        cout << "\nChoose faculty for " << db->courseCodes[c] << ":\n";
        for (int f = 0; f < db->facultyCount; f++)
            cout << "  " << f << ") " << db->faculty[f] << "\n";

        int choice;
        cin >> choice;
        clearInput();

        if (choice < 0 || choice >= db->facultyCount) choice = 0;

        courseToFaculty[c] = choice;
    }

    //Assign a DEFAULT value for un-selected courses
    for (int i = 0; i < db->courseCount; i++) {
        bool assigned = false;
        for (int j = 0; j < n; j++) {
            if (selected[j] == i) {
                assigned = true;
                break;
            }
        }
        if (!assigned) courseToFaculty[i] = 0;  // default
    }

    delete[] selected;

    cout << "\nFaculty assignment complete (selected + default).\n";
}

void FunctionsModule::mapFacultyToRoom() {
    if (!db || db->facultyCount == 0 || db->roomCount == 0) {
        cout << "Database empty.\n";
        return;
    }

    facultyToRoom = new int[db->facultyCount];

    cout << "\nAssign Faculty -> Room\n";
    for (int f = 0; f < db->facultyCount; f++) {
        cout << "\nChoose room index for " << db->faculty[f] << ":\n";
        for (int r = 0; r < db->roomCount; r++)
            cout << r << ") " << db->rooms[r] << "\n";
        cin >> facultyToRoom[f];
    }
}



//FUNCTION PROPERTIES

void FunctionsModule::checkInjective() {
    cout << "\nChecking Injective properties:\n";

    // Student -> Course
    if (db && studentToCourse && db->studentCount > 0 && db->courseCount > 0) {
        bool inj = true;
        for (int i = 0; i < db->studentCount && inj; i++) {
            for (int j = i + 1; j < db->studentCount; j++) {
                if (studentToCourse[i] == studentToCourse[j]) {
                    inj = false;
                    break;
                }
            }
        }
        cout << "Student -> Course: " << (inj ? "Injective" : "NOT Injective") << "\n";
    }
    else {
        cout << "Student -> Course: (mapping not defined)\n";
    }

    // Course -> Faculty
    if (db && courseToFaculty && db->courseCount > 0 && db->facultyCount > 0) {
        bool inj = true;
        for (int i = 0; i < db->courseCount && inj; i++) {
            for (int j = i + 1; j < db->courseCount; j++) {
                if (courseToFaculty[i] == courseToFaculty[j]) {
                    inj = false;
                    break;
                }
            }
        }
        cout << "Course -> Faculty: " << (inj ? "Injective" : "NOT Injective") << "\n";
    }
    else {
        cout << "Course -> Faculty: (mapping not defined)\n";
    }

    // Faculty -> Room
    if (db && facultyToRoom && db->facultyCount > 0 && db->roomCount > 0) {
        bool inj = true;
        for (int i = 0; i < db->facultyCount && inj; i++) {
            for (int j = i + 1; j < db->facultyCount; j++) {
                if (facultyToRoom[i] == facultyToRoom[j]) {
                    inj = false;
                    break;
                }
            }
        }
        cout << "Faculty -> Room: " << (inj ? "Injective" : "NOT Injective") << "\n";
    }
    else {
        cout << "Faculty -> Room: (mapping not defined)\n";
    }
}
void FunctionsModule::checkSurjective() {
    cout << "\nChecking Surjective (onto) properties:\n";

    // Student -> Course
    if (db && studentToCourse && db->studentCount > 0 && db->courseCount > 0) {
        bool* covered = new bool[db->courseCount]();
        for (int i = 0; i < db->studentCount; i++) {
            int idx = studentToCourse[i];
            if (idx >= 0 && idx < db->courseCount)
                covered[idx] = true;
        }
        bool ok = true;
        for (int i = 0; i < db->courseCount; i++) {
            if (!covered[i]) {
                ok = false;
                break;
            }
        }
        delete[] covered;
        cout << "Student -> Course: " << (ok ? "Surjective" : "NOT Surjective") << "\n";
    }
    else {
        cout << "Student -> Course: (mapping not defined)\n";
    }

    // Course -> Faculty
    if (db && courseToFaculty && db->courseCount > 0 && db->facultyCount > 0) {
        bool* covered = new bool[db->facultyCount]();
        for (int i = 0; i < db->courseCount; i++) {
            int idx = courseToFaculty[i];
            if (idx >= 0 && idx < db->facultyCount)
                covered[idx] = true;
        }
        bool ok = true;
        for (int i = 0; i < db->facultyCount; i++) {
            if (!covered[i]) {
                ok = false;
                break;
            }
        }
        delete[] covered;
        cout << "Course -> Faculty: " << (ok ? "Surjective" : "NOT Surjective") << "\n";
    }
    else {
        cout << "Course -> Faculty: (mapping not defined)\n";
    }

    // Faculty -> Room
    if (db && facultyToRoom && db->facultyCount > 0 && db->roomCount > 0) {
        bool* covered = new bool[db->roomCount]();
        for (int i = 0; i < db->facultyCount; i++) {
            int idx = facultyToRoom[i];
            if (idx >= 0 && idx < db->roomCount)
                covered[idx] = true;
        }
        bool ok = true;
        for (int i = 0; i < db->roomCount; i++) {
            if (!covered[i]) {
                ok = false;
                break;
            }
        }
        delete[] covered;
        cout << "Faculty -> Room: " << (ok ? "Surjective" : "NOT Surjective") << "\n";
    }
    else {
        cout << "Faculty -> Room: (mapping not defined)\n";
    }
}

void FunctionsModule::checkBijective() {
    cout << "\nChecking Bijective properties:\n";

    //Student -> Course
    if (db && studentToCourse && db->studentCount > 0 && db->courseCount > 0) {
        bool sizeOk = (db->studentCount == db->courseCount);

        // injective
        bool inj = true;
        for (int i = 0; i < db->studentCount && inj; i++) {
            for (int j = i + 1; j < db->studentCount; j++) {
                if (studentToCourse[i] == studentToCourse[j]) {
                    inj = false;
                    break;
                }
            }
        }

        // surjective
        bool* covered = new bool[db->courseCount]();
        for (int i = 0; i < db->studentCount; i++) {
            int idx = studentToCourse[i];
            if (idx >= 0 && idx < db->courseCount)
                covered[idx] = true;
        }
        bool surj = true;
        for (int i = 0; i < db->courseCount; i++) {
            if (!covered[i]) {
                surj = false;
                break;
            }
        }
        delete[] covered;

        bool bij = sizeOk && inj && surj;
        cout << "Student -> Course: " << (bij ? "Bijective" : "NOT Bijective") << "\n";
    }
    else {
        cout << "Student -> Course: (mapping not defined)\n";
    }

    // Course -> Faculty 
    if (db && courseToFaculty && db->courseCount > 0 && db->facultyCount > 0) {
        bool sizeOk = (db->courseCount == db->facultyCount);

        bool inj = true;
        for (int i = 0; i < db->courseCount && inj; i++) {
            for (int j = i + 1; j < db->courseCount; j++) {
                if (courseToFaculty[i] == courseToFaculty[j]) {
                    inj = false;
                    break;
                }
            }
        }

        bool* covered = new bool[db->facultyCount]();
        for (int i = 0; i < db->courseCount; i++) {
            int idx = courseToFaculty[i];
            if (idx >= 0 && idx < db->facultyCount)
                covered[idx] = true;
        }
        bool surj = true;
        for (int i = 0; i < db->facultyCount; i++) {
            if (!covered[i]) {
                surj = false;
                break;
            }
        }
        delete[] covered;

        bool bij = sizeOk && inj && surj;
        cout << "Course -> Faculty: " << (bij ? "Bijective" : "NOT Bijective") << "\n";
    }
    else {
        cout << "Course -> Faculty: (mapping not defined)\n";
    }

    // Faculty -> Room 
    if (db && facultyToRoom && db->facultyCount > 0 && db->roomCount > 0) {
        bool sizeOk = (db->facultyCount == db->roomCount);

        bool inj = true;
        for (int i = 0; i < db->facultyCount && inj; i++) {
            for (int j = i + 1; j < db->facultyCount; j++) {
                if (facultyToRoom[i] == facultyToRoom[j]) {
                    inj = false;
                    break;
                }
            }
        }

        bool* covered = new bool[db->roomCount]();
        for (int i = 0; i < db->facultyCount; i++) {
            int idx = facultyToRoom[i];
            if (idx >= 0 && idx < db->roomCount)
                covered[idx] = true;
        }
        bool surj = true;
        for (int i = 0; i < db->roomCount; i++) {
            if (!covered[i]) {
                surj = false;
                break;
            }
        }
        delete[] covered;

        bool bij = sizeOk && inj && surj;
        cout << "Faculty -> Room: " << (bij ? "Bijective" : "NOT Bijective") << "\n";
    }
    else {
        cout << "Faculty -> Room: (mapping not defined)\n";
    }
}

//INVERSE & COMPOSITION

void FunctionsModule::inverseCourseFaculty() {
    cout << "\nFaculty -> Courses\n";
    for (int f = 0; f < db->facultyCount; f++) {
        cout << db->faculty[f] << " -> ";
        bool found = false;

        for (int c = 0; c < db->courseCount; c++)
            if (courseToFaculty[c] == f) {
                cout << db->courseCodes[c] << " ";
                found = true;
            }
        if (!found) cout << "No Course";
        cout << "\n";
    }
}

void FunctionsModule::composeStudentFaculty() {
    cout << "\nStudent -> Faculty (Composition)\n";
    for (int s = 0; s < db->studentCount; s++) {
        int c = studentToCourse[s];
        int f = courseToFaculty[c];
        cout << db->students[s] << " -> " << db->faculty[f] << "\n";
    }
}

void FunctionsModule::displayMappings() {
    cout << "\nMappings:\n";

    cout << "\nStudent -> Course\n";
    for (int s = 0; s < db->studentCount; s++)
        cout << db->students[s] << " -> " << db->courseCodes[studentToCourse[s]] << "\n";

    cout << "\nCourse -> Faculty\n";
    for (int c = 0; c < db->courseCount; c++)
        cout << db->courseCodes[c] << " -> " << db->faculty[courseToFaculty[c]] << "\n";

    cout << "\nFaculty -> Room\n";
    for (int f = 0; f < db->facultyCount; f++)
        cout << db->faculty[f] << " -> " << db->rooms[facultyToRoom[f]] << "\n";
}