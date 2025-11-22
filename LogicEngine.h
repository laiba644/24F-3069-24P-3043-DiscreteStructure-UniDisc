#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <iostream>
#include <string>
using namespace std;

class CourseScheduling;
class UniversityDatabase;   // forward declaration

class LogicEngine {
public:
    struct Rule {
        string ruleType;    // e.g. "PREREQUISITE", "FACULTY_ASSIGNMENT"
        string condition;   // e.g. "STUDENT ENROLLED CS2001"
        string conclusion;  // e.g. "STUDENT MUST_COMPLETE CS1004"
        bool isActive;

        Rule();
        Rule(const string& type, const string& cond, const string& concl);
    };

    struct Fact {
        string factType;    // e.g. "STUDENT_ENROLLED"
        string subject;     // e.g. "S001"
        string predicate;   // e.g. "ENROLLED_IN"
        string object;      // e.g. "CS1004"
        bool isTrue;

        Fact();
        Fact(const string& type, const string& subj,
            const string& pred, const string& obj,
            bool truth = true);
    };

private:
    // internal helpers
    void resizeRules();
    void resizeFacts();
    void resizeKB();

    bool matchesPattern(const string& pattern, const string& fact);
    bool evaluateCondition(const string& condition);

    bool modusPonens(const Rule& rule);
    bool modusTollens(const Rule& rule);        // basic stub implementation
    bool backwardChaining(const string& goal);  // basic stub implementation

public:
    CourseScheduling* courseSystem;   // pointer to course/prereq system
    UniversityDatabase* uniDB;        // pointer to university DB (students, faculty, rooms)

    Rule** rules;
    int ruleCount;
    int ruleCapacity;

    Fact** facts;
    int factCount;
    int factCapacity;

    // simple KB as triples: [subject][predicate][object]
    string** knowledgeBase;
    int kbCount;
    int kbCapacity;

    // predicate list for discrete math demonstration / quantifiers
    string* predicateNames;
    int predicateCount;
    int predicateCapacity;

public:
    LogicEngine(CourseScheduling* ptr);
    ~LogicEngine();

    // optional: link database after construction
    void setDatabase(UniversityDatabase* dbPtr);

    // rule management
    void addRule(const string& type, const string& condition, const string& conclusion);
    void displayRules();
    void enableRule(int index);
    void disableRule(int index);

    // fact management
    void addFact(const string& type, const string& subject,
        const string& predicate, const string& object,
        bool truth = true);
    void displayFacts();
    bool checkFact(const string& type, const string& subject,
        const string& predicate, const string& object);

    // inference
    void forwardChaining();
    void inferNewFacts();
    void verifyAllRules();
    bool queryKnowledgeBase(const string& query);

    // domain-specific conflict checks
    void detectCourseConflicts();
    void detectFacultyConflicts();
    void detectLabConflicts();

    // automatic rule generation
    void loadDefaultRules();  // now uses CourseScheduling data (no hard-coded courses)
    void addPrerequisiteRule(const string& course, const string& prerequisite);
    void addFacultyAssignmentRule(const string& faculty,
        const string& course,
        const string& lab);
    void addTimeConflictRule(const string& course1, const string& course2);

    // verification helpers
    bool verifyStudentEnrollment(const string& studentID, const string& courseCode);
    bool verifyFacultyAssignment(const string& facultyID, const string& courseCode);
    bool verifyLabAllocation(const string& courseCode, const string& labID);

    // propositional logic (simple, clean output)
    bool isTautology(const string& proposition);

    // predicate logic
    void addPredicate(const string& name, const string& var1, const string& var2 = "");
    void displayPredicates();
    bool checkPredicate(const string& predicateName,
        const string& arg1,
        const string& arg2 = "");

    bool universalQuantifier(const string& predicateName, string domain[], int size);
    bool existentialQuantifier(const string& predicateName, string domain[], int size);

    // reports
    void generateInferenceReport();
    void displayKnowledgeBase();
};

#endif
