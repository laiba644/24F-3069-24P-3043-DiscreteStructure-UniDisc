#ifndef FUNCTIONSMODULE_H
#define FUNCTIONSMODULE_H

#include <string>
using namespace std;

class UniversityDatabase;

class FunctionsModule {
private:
    UniversityDatabase* db;    

    int* studentToCourse;       // Student -> Course mapping
    int* courseToFaculty;       // Course -> Faculty mapping
    int* facultyToRoom;         // Faculty -> Room mapping

public:
    FunctionsModule(UniversityDatabase* ptr = nullptr);
    ~FunctionsModule();

    void attachDatabase(UniversityDatabase* ptr);

    
    void mapStudentToCourse();
    void mapCourseToFaculty();
    void mapFacultyToRoom();

    // FUNCTION PROPERTIES
    void checkInjective();
    void checkSurjective();
    void checkBijective();

    // INVERSE & COMPOSITION
    void inverseCourseFaculty();
    void composeStudentFaculty();

    // SHOW ALL MAPS
    void displayMappings();
};

#endif