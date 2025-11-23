#include "SetOperations.h"
#include "UniversityDatabase.h"

// -------------------- Set struct --------------------

SetOperations::Set::Set() {
    name = "";
    size = 0;
    capacity = 10;
    elements = new string[capacity];
}

SetOperations::Set::Set(const string& setName) {
    name = setName;
    size = 0;
    capacity = 10;
    elements = new string[capacity];
}

SetOperations::Set::~Set() {
    delete[] elements;
}

void SetOperations::Set::addElement(const string& element) {
    // Avoid duplicates
    if (contains(element)) return;

    if (size >= capacity) {
        capacity *= 2;
        string* temp = new string[capacity];
        for (int i = 0; i < size; i++)
            temp[i] = elements[i];
        delete[] elements;
        elements = temp;
    }
    elements[size++] = element;
}

bool SetOperations::Set::contains(const string& element) const {
    for (int i = 0; i < size; i++) {
        if (elements[i] == element)
            return true;
    }
    return false;
}

void SetOperations::Set::display() const {
    cout << name << " = {";
    for (int i = 0; i < size; i++) {
        cout << elements[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "}\n";
    cout << "Cardinality |" << name << "| = " << size << "\n";
}

void SetOperations::Set::clear() {
    size = 0;
}

// -------------------- SetOperations core --------------------

SetOperations::SetOperations(UniversityDatabase* dbPtr) {
    setCount = 0;
    setCapacity = 10;
    sets = new Set * [setCapacity];
    db = dbPtr;
}

SetOperations::~SetOperations() {
    for (int i = 0; i < setCount; i++)
        delete sets[i];
    delete[] sets;
}

void SetOperations::attachDatabase(UniversityDatabase* dbPtr) {
    db = dbPtr;
}

void SetOperations::resizeSets() {
    setCapacity *= 2;
    Set** temp = new Set * [setCapacity];
    for (int i = 0; i < setCount; i++)
        temp[i] = sets[i];
    delete[] sets;
    sets = temp;
}

int SetOperations::findSetIndex(const string& setName) const {
    for (int i = 0; i < setCount; i++) {
        if (sets[i]->name == setName)
            return i;
    }
    return -1;
}

void SetOperations::removeElement(string* arr, int& size, int index) {
    for (int i = index; i < size - 1; i++)
        arr[i] = arr[i + 1];
    size--;
}

// -------------------- Generic set API --------------------

void SetOperations::createSet(const string& setName) {
    if (findSetIndex(setName) != -1) {
        cout << "Set '" << setName << "' already exists.\n";
        return;
    }
    if (setCount >= setCapacity)
        resizeSets();

    sets[setCount++] = new Set(setName);
    cout << "Set '" << setName << "' created.\n";
}

void SetOperations::addElementToSet(const string& setName, const string& element) {
    int index = findSetIndex(setName);
    if (index == -1) {
        cout << "Set '" << setName << "' not found.\n";
        return;
    }
    sets[index]->addElement(element);
}

void SetOperations::displaySet(const string& setName) const {
    int index = findSetIndex(setName);
    if (index == -1) {
        cout << "Set '" << setName << "' not found.\n";
        return;
    }
    sets[index]->display();
}

void SetOperations::displayAllSets() const {
    cout << "\nCurrent Sets\n\n";
    if (setCount == 0) {
        cout << "No sets created yet.\n";
        return;
    }
    for (int i = 0; i < setCount; i++) {
        sets[i]->display();
        cout << "\n";
    }
}

SetOperations::Set* SetOperations::getSet(const string& setName) const {
    int index = findSetIndex(setName);
    if (index == -1)
        return nullptr;
    return sets[index];
}

SetOperations::Set* SetOperations::unionSets(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }

    Set* result = new Set(setA + "_UNION_" + setB);
    for (int i = 0; i < a->size; i++)
        result->addElement(a->elements[i]);
    for (int i = 0; i < b->size; i++)
        result->addElement(b->elements[i]);

    return result;
}

SetOperations::Set* SetOperations::intersectionSets(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }

    Set* result = new Set(setA + "_INTERSECTION_" + setB);
    for (int i = 0; i < a->size; i++) {
        if (b->contains(a->elements[i]))
            result->addElement(a->elements[i]);
    }
    return result;
}

SetOperations::Set* SetOperations::differenceSets(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }

    Set* result = new Set(setA + "_MINUS_" + setB);
    for (int i = 0; i < a->size; i++) {
        if (!b->contains(a->elements[i]))
            result->addElement(a->elements[i]);
    }
    return result;
}

bool SetOperations::isSubset(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return false;
    }
    for (int i = 0; i < a->size; i++) {
        if (!b->contains(a->elements[i]))
            return false;
    }
    return true;
}

bool SetOperations::isSuperset(const string& setA, const string& setB) const {
    return isSubset(setB, setA);
}

bool SetOperations::isProperSubset(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) return false;
    return isSubset(setA, setB) && (a->size < b->size);
}

bool SetOperations::areDisjoint(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) return false;

    for (int i = 0; i < a->size; i++) {
        if (b->contains(a->elements[i]))
            return false;
    }
    return true;
}

bool SetOperations::areEqual(const string& setA, const string& setB) const {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) return false;
    if (a->size != b->size) return false;
    return isSubset(setA, setB);
}

int SetOperations::cardinality(const string& setName) const {
    Set* s = getSet(setName);
    if (!s) return -1;
    return s->size;
}

void SetOperations::generatePowerSet(const string& setName) {
    Set* s = getSet(setName);
    if (!s) {
        cout << "Set not found.\n";
        return;
    }

    int powerSetSize = 1;
    for (int i = 0; i < s->size; i++)
        powerSetSize *= 2;

    cout << "\nPower set of " << s->name << "\n";
    cout << "Total subsets: " << powerSetSize << "\n\n";

    for (int mask = 0; mask < powerSetSize; mask++) {
        cout << "{";
        bool first = true;
        for (int j = 0; j < s->size; j++) {
            if (mask & (1 << j)) {
                if (!first) cout << ", ";
                cout << s->elements[j];
                first = false;
            }
        }
        cout << "}\n";
    }
}

void SetOperations::cartesianProduct(const string& setA, const string& setB) {
    Set* a = getSet(setA);
    Set* b = getSet(setB);
    if (!a || !b) {
        cout << "One or both sets not found.\n";
        return;
    }

    cout << "\nCartesian product " << a->name << " x " << b->name << ":\n";
    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < b->size; j++) {
            cout << "(" << a->elements[i] << ", " << b->elements[j] << ")\n";
        }
    }
    cout << "Total pairs: " << a->size * b->size << "\n";
}

SetOperations::Set* SetOperations::complement(const string& setName, const string& universalSetName) {
    Set* s = getSet(setName);
    Set* u = getSet(universalSetName);
    if (!s || !u) {
        cout << "One or both sets not found.\n";
        return nullptr;
    }

    Set* result = new Set(setName + "_COMPLEMENT");
    for (int i = 0; i < u->size; i++) {
        if (!s->contains(u->elements[i]))
            result->addElement(u->elements[i]);
    }
    return result;
}

// -------------------- DB-backed helpers --------------------

// Build set of all students registered in a specific course (from UniversityDatabase)
void SetOperations::buildCourseStudentSet(const string& courseCode, Set& result) const {
    result.clear();
    result.name = courseCode;

    if (!db) {
        cout << "SetOperations: no UniversityDatabase attached.\n";
        return;
    }

    // We assume UniversityDatabase exposes:
    //   int studentCount;
    //   string* students;
    //   string** studentCourses;
    //   int* courseCountOfStudent;
    // and that course codes in studentCourses match courseCode
    for (int s = 0; s < db->studentCount; s++) {
        for (int k = 0; k < db->courseCountOfStudent[s]; k++) {
            if (db->studentCourses[s][k] == courseCode) {
                result.addElement(db->students[s]);
                break; // no need to check more courses for this student
            }
        }
    }
}

// Students in intersection of 2 courses
void SetOperations::findStudentsInBothCourses(const string& course1, const string& course2) {
    if (!db) {
        cout << "SetOperations: no UniversityDatabase attached.\n";
        return;
    }

    Set s1(course1);
    Set s2(course2);
    buildCourseStudentSet(course1, s1);
    buildCourseStudentSet(course2, s2);

    Set result("Students_in_both_" + course1 + "_" + course2);
    for (int i = 0; i < s1.size; i++) {
        if (s2.contains(s1.elements[i]))
            result.addElement(s1.elements[i]);
    }

    cout << "\nStudents enrolled in both " << course1 << " and " << course2 << ":\n";
    if (result.size == 0) {
        cout << "None\n";
    }
    else {
        for (int i = 0; i < result.size; i++) {
            cout << "  " << (i + 1) << ". " << result.elements[i] << "\n";
        }
        cout << "Total: " << result.size << " students\n";
    }
}

// Students in union of 2 courses
void SetOperations::findStudentsInEitherCourse(const string& course1, const string& course2) {
    if (!db) {
        cout << "SetOperations: no UniversityDatabase attached.\n";
        return;
    }

    Set s1(course1);
    Set s2(course2);
    buildCourseStudentSet(course1, s1);
    buildCourseStudentSet(course2, s2);

    Set result("Students_in_" + course1 + "_or_" + course2);
    for (int i = 0; i < s1.size; i++)
        result.addElement(s1.elements[i]);
    for (int i = 0; i < s2.size; i++)
        result.addElement(s2.elements[i]);

    cout << "\nStudents enrolled in " << course1 << " or " << course2 << ":\n";
    if (result.size == 0) {
        cout << "None\n";
    }
    else {
        for (int i = 0; i < result.size; i++) {
            cout << "  " << (i + 1) << ". " << result.elements[i] << "\n";
        }
        cout << "Total: " << result.size << " students\n";
    }
}

// Students in symmetric difference of 2 courses
void SetOperations::findStudentsOnlyInOneCourse(const string& course1, const string& course2) {
    if (!db) {
        cout << "SetOperations: no UniversityDatabase attached.\n";
        return;
    }

    Set s1(course1);
    Set s2(course2);
    buildCourseStudentSet(course1, s1);
    buildCourseStudentSet(course2, s2);

    Set result("Students_only_in_one_of_" + course1 + "_" + course2);

    // In course1 but not course2
    for (int i = 0; i < s1.size; i++) {
        if (!s2.contains(s1.elements[i]))
            result.addElement(s1.elements[i]);
    }
    // In course2 but not course1
    for (int i = 0; i < s2.size; i++) {
        if (!s1.contains(s2.elements[i]))
            result.addElement(s2.elements[i]);
    }

    cout << "\nStudents enrolled in exactly one of " << course1 << " or " << course2 << ":\n";
    if (result.size == 0) {
        cout << "None\n";
    }
    else {
        for (int i = 0; i < result.size; i++) {
            cout << "  " << (i + 1) << ". " << result.elements[i] << "\n";
        }
        cout << "Total: " << result.size << " students\n";
    }
}

// Faculties common between two manually created department sets
void SetOperations::findCommonFaculties(const string& dept1, const string& dept2) {
    Set* result = intersectionSets(dept1, dept2);
    cout << "\nCommon faculties between " << dept1 << " and " << dept2 << ":\n";
    if (!result || result->size == 0) {
        cout << "None\n";
    }
    else {
        for (int i = 0; i < result->size; i++) {
            cout << "  " << (i + 1) << ". " << result->elements[i] << "\n";
        }
        cout << "Total: " << result->size << " faculties\n";
    }
    delete result;
}
int SetOperations::getStudentsInCourse(const string& courseCode, bitset<100>& bs) {
    bs.reset();

    Set temp(courseCode);
    buildCourseStudentSet(courseCode, temp);

    for (int i = 0; i < temp.size; i++)
        bs.set(i);

    return temp.size;
}
