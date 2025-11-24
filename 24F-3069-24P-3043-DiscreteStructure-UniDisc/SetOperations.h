#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <iostream>
#include <string>
#include <bitset>
using namespace std;


class UniversityDatabase;

class SetOperations {
public:
    struct Set {
        string name;
        string* elements;
        int size;
        int capacity;

        Set();
        Set(const string& setName);
        ~Set();

        void addElement(const string& element);
        bool contains(const string& element) const;
        void display() const;
        void clear();
    };

private:
    Set** sets;
    int setCount;
    int setCapacity;

    // Link to central university data
    UniversityDatabase* db;

    void resizeSets();
    int findSetIndex(const string& setName) const;
    void removeElement(string* arr, int& size, int index);

    
    void buildCourseStudentSet(const string& courseCode, Set& result) const;

public:
    
    SetOperations(UniversityDatabase* dbPtr = nullptr);
    ~SetOperations();

    void attachDatabase(UniversityDatabase* dbPtr);

    
    void createSet(const string& setName);
    void addElementToSet(const string& setName, const string& element);
    void displaySet(const string& setName) const;
    void displayAllSets() const;
    Set* getSet(const string& setName) const;

    Set* unionSets(const string& setA, const string& setB);
    Set* intersectionSets(const string& setA, const string& setB);
    Set* differenceSets(const string& setA, const string& setB);

    bool isSubset(const string& setA, const string& setB) const;
    bool isSuperset(const string& setA, const string& setB) const;
    bool isProperSubset(const string& setA, const string& setB) const;
    bool areDisjoint(const string& setA, const string& setB) const;
    bool areEqual(const string& setA, const string& setB) const;

    int cardinality(const string& setName) const;

    void generatePowerSet(const string& setName);
    void cartesianProduct(const string& setA, const string& setB);
    Set* complement(const string& setName, const string& universalSetName);

    

    //  (intersection)
    void findStudentsInBothCourses(const string& course1, const string& course2);

    //  (union)
    void findStudentsInEitherCourse(const string& course1, const string& course2);

    // Students enrolled in exactly one of the two courses (symmetric difference)
    void findStudentsOnlyInOneCourse(const string& course1, const string& course2);

    
    void findCommonFaculties(const string& dept1, const string& dept2);
    int getStudentsInCourse(const string& courseCode, bitset<100>& bs);

};

#endif