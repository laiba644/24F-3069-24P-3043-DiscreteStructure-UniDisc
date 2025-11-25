#include "LogicEngine.h"
#include "CourseScheduling.h"
#include "UniversityDatabase.h"
#include <sstream>

// ======================= Rule & Fact =======================

LogicEngine::Rule::Rule() {
    isActive = true;
}

LogicEngine::Rule::Rule(const string& type,
    const string& cond,
    const string& concl) {
    ruleType = type;
    condition = cond;
    conclusion = concl;
    isActive = true;
}

LogicEngine::Fact::Fact() {
    isTrue = true;
}

LogicEngine::Fact::Fact(const string& type,
    const string& subj,
    const string& pred,
    const string& obj,
    bool truth) {
    factType = type;
    subject = subj;
    predicate = pred;
    object = obj;
    isTrue = truth;
}

// ======================= ctor / dtor =======================

LogicEngine::LogicEngine(CourseScheduling* ptr) {
    courseSystem = ptr;
    uniDB = nullptr;

    // rules
    ruleCount = 0;
    ruleCapacity = 20;
    rules = new Rule * [ruleCapacity];

    // facts
    factCount = 0;
    factCapacity = 50;
    facts = new Fact * [factCapacity];

    // knowledge base (triples)
    kbCount = 0;
    kbCapacity = 100;
    knowledgeBase = new string * [kbCapacity];
    for (int i = 0; i < kbCapacity; ++i)
        knowledgeBase[i] = new string[3];

    // predicate names
    predicateCount = 0;
    predicateCapacity = 20;
    predicateNames = new string[predicateCapacity];
}

LogicEngine::~LogicEngine() {
    // rules
    for (int i = 0; i < ruleCount; ++i)
        delete rules[i];
    delete[] rules;

    // facts
    for (int i = 0; i < factCount; ++i)
        delete facts[i];
    delete[] facts;

    // knowledge base
    for (int i = 0; i < kbCapacity; ++i)
        delete[] knowledgeBase[i];
    delete[] knowledgeBase;

    // predicates
    delete[] predicateNames;
}

void LogicEngine::setDatabase(UniversityDatabase* dbPtr) {
    uniDB = dbPtr;
}

// ======================= internal resize helpers =======================

void LogicEngine::resizeRules() {
    ruleCapacity *= 2;
    Rule** temp = new Rule * [ruleCapacity];
    for (int i = 0; i < ruleCount; ++i)
        temp[i] = rules[i];
    delete[] rules;
    rules = temp;
}

void LogicEngine::resizeFacts() {
    factCapacity *= 2;
    Fact** temp = new Fact * [factCapacity];
    for (int i = 0; i < factCount; ++i)
        temp[i] = facts[i];
    delete[] facts;
    facts = temp;
}

void LogicEngine::resizeKB() {
    int newCap = kbCapacity * 2;
    string** temp = new string * [newCap];
    for (int i = 0; i < newCap; ++i) {
        temp[i] = new string[3];
        if (i < kbCapacity) {
            temp[i][0] = knowledgeBase[i][0];
            temp[i][1] = knowledgeBase[i][1];
            temp[i][2] = knowledgeBase[i][2];
        }
    }
    for (int i = 0; i < kbCapacity; ++i)
        delete[] knowledgeBase[i];
    delete[] knowledgeBase;
    knowledgeBase = temp;
    kbCapacity = newCap;
}

// ======================= rule management =======================

void LogicEngine::addRule(const string& type,
    const string& condition,
    const string& conclusion) {
    if (ruleCount >= ruleCapacity)
        resizeRules();

    rules[ruleCount++] = new Rule(type, condition, conclusion);
    cout << "Rule added: IF " << condition
        << " THEN " << conclusion << endl;
}

void LogicEngine::displayRules() {
    cout << "\nLOGICAL RULES\n\n";

    if (ruleCount == 0) {
        cout << "No rules defined." << endl;
        return;
    }

    for (int i = 0; i < ruleCount; ++i) {
        cout << "Rule " << (i + 1)
            << " [" << rules[i]->ruleType << "] "
            << (rules[i]->isActive ? "(active)" : "(inactive)") << endl;

        cout << "  IF   " << rules[i]->condition << endl;
        cout << "  THEN " << rules[i]->conclusion << endl;
    }
}

void LogicEngine::enableRule(int index) {
    if (index >= 0 && index < ruleCount) {
        rules[index]->isActive = true;
        cout << "Rule " << (index + 1) << " enabled." << endl;
    }
}

void LogicEngine::disableRule(int index) {
    if (index >= 0 && index < ruleCount) {
        rules[index]->isActive = false;
        cout << "Rule " << (index + 1) << " disabled." << endl;
    }
}

// ======================= fact management =======================

void LogicEngine::addFact(const string& type,
    const string& subject,
    const string& predicate,
    const string& object,
    bool truth) {
    if (factCount >= factCapacity)
        resizeFacts();

    facts[factCount++] = new Fact(type, subject, predicate, object, truth);

    if (!truth) return; // false facts are not added to KB

    if (kbCount >= kbCapacity)
        resizeKB();

    knowledgeBase[kbCount][0] = subject;
    knowledgeBase[kbCount][1] = predicate;
    knowledgeBase[kbCount][2] = object;
    ++kbCount;
}

void LogicEngine::displayFacts() {
    cout << "\nKNOWN FACTS\n\n";

    if (factCount == 0) {
        cout << "No facts in knowledge base." << endl;
        return;
    }

    for (int i = 0; i < factCount; ++i) {
        cout << (i + 1) << ". "
            << "[" << facts[i]->factType << "] "
            << facts[i]->subject << " "
            << facts[i]->predicate << " "
            << facts[i]->object;

        if (!facts[i]->isTrue)
            cout << " (false)";
        cout << endl;
    }
}

bool LogicEngine::checkFact(const string& type,
    const string& subject,
    const string& predicate,
    const string& object) {
    for (int i = 0; i < factCount; ++i) {
        if (facts[i]->factType == type &&
            facts[i]->subject == subject &&
            facts[i]->predicate == predicate &&
            facts[i]->object == object &&
            facts[i]->isTrue) {
            return true;
        }
    }
    return false;
}

// ======================= pattern / condition helpers =======================

bool LogicEngine::matchesPattern(const string& pattern,
    const string& fact) {
    // very simple: exact match or pattern contains '*'
    if (pattern == fact) return true;
    if (pattern.find('*') != string::npos) return true;
    return false;
}

bool LogicEngine::evaluateCondition(const string& condition) {
    // condition format: SUBJECT PREDICATE OBJECT
    stringstream ss(condition);
    string subject, predicate, object;
    ss >> subject >> predicate >> object;

    for (int i = 0; i < kbCount; ++i) {
        if (knowledgeBase[i][0] == subject &&
            knowledgeBase[i][1] == predicate &&
            knowledgeBase[i][2] == object) {
            return true;
        }
    }
    return false;
}

// ======================= inference: modus ponens / tollens =======================

bool LogicEngine::modusPonens(const Rule& rule) {
    if (!rule.isActive)
        return false;

    if (!evaluateCondition(rule.condition))
        return false;

    // add conclusion to KB if not already present
    stringstream ss(rule.conclusion);
    string subject, predicate, object;
    ss >> subject >> predicate >> object;

    for (int i = 0; i < kbCount; ++i) {
        if (knowledgeBase[i][0] == subject &&
            knowledgeBase[i][1] == predicate &&
            knowledgeBase[i][2] == object) {
            return false; // already known
        }
    }

    if (kbCount >= kbCapacity)
        resizeKB();

    knowledgeBase[kbCount][0] = subject;
    knowledgeBase[kbCount][1] = predicate;
    knowledgeBase[kbCount][2] = object;
    ++kbCount;

    cout << "Inferred (modus ponens): " << rule.conclusion << endl;
    return true;
}

bool LogicEngine::modusTollens(const Rule& rule) {
    // Simple placeholder:
    // IF (P -> Q) and NOT Q, then NOT P
    // representation is too simple to fully support, so we just log that
    // this rule is not handled structurally.
    (void)rule; // avoid unused warning
    // You can extend this later if needed.
    return false;
}

// ======================= forward / backward chaining =======================

void LogicEngine::forwardChaining() {
    cout << "\nFORWARD CHAINING INFERENCE\n\n";

    bool newInference = true;
    int iterations = 0;

    while (newInference && iterations < 50) {
        newInference = false;
        ++iterations;

        for (int i = 0; i < ruleCount; ++i) {
            if (modusPonens(*rules[i])) {
                newInference = true;
            }
        }
    }

    cout << "Forward chaining completed after "
        << iterations << " iteration(s)." << endl;
}

void LogicEngine::inferNewFacts() {
    forwardChaining();
}

bool LogicEngine::backwardChaining(const string& goal) {
    // Very simple backward check:
    // if goal already in KB, return true
    for (int i = 0; i < kbCount; ++i) {
        string triple = knowledgeBase[i][0] + " " +
            knowledgeBase[i][1] + " " +
            knowledgeBase[i][2];
        if (triple == goal)
            return true;
    }
    // full backward-chaining search can be added later
    return false;
}

bool LogicEngine::queryKnowledgeBase(const string& query) {
    // query format: SUBJECT PREDICATE OBJECT
    stringstream ss(query);
    string subject, predicate, object;
    ss >> subject >> predicate >> object;

    for (int i = 0; i < kbCount; ++i) {
        if (knowledgeBase[i][0] == subject &&
            knowledgeBase[i][1] == predicate &&
            knowledgeBase[i][2] == object) {
            return true;
        }
    }
    return false;
}

// ======================= rule verification =======================

void LogicEngine::verifyAllRules() {
    cout << "\nRULE VERIFICATION\n\n";

    int satisfied = 0;
    int violated = 0;

    for (int i = 0; i < ruleCount; ++i) {
        if (!rules[i]->isActive) continue;

        bool conditionMet = evaluateCondition(rules[i]->condition);
        bool conclusionMet = evaluateCondition(rules[i]->conclusion);

        cout << "Rule " << (i + 1) << ": ";

        if (conditionMet && conclusionMet) {
            cout << "satisfied";
            ++satisfied;
        }
        else if (conditionMet && !conclusionMet) {
            cout << "violated (condition true, conclusion false)";
            ++violated;
        }
        else {
            cout << "not applicable (condition false)";
        }
        cout << endl;
    }

    cout << "\nSummary: "
        << "satisfied = " << satisfied
        << ", violated = " << violated << endl;
}

// ======================= domain-specific conflict checks =======================

void LogicEngine::detectCourseConflicts() {
    cout << "\nCOURSE CONFLICT DETECTION\n\n";

    if (!courseSystem) {
        cout << "Course system not attached.\n";
        return;
    }

    int conflicts = 0;

    for (int i = 0; i < factCount; ++i) {
        if (facts[i]->factType == "STUDENT_ENROLLED") {
            string studentID = facts[i]->subject;
            string courseCode = facts[i]->object;

            CourseScheduling::Course* course =
                courseSystem->findCourse(courseCode);

            if (!course) continue;

            for (int j = 0; j < course->prereqCount; ++j) {
                string prereq = course->prerequisites[j];

                bool completed = false;
                for (int k = 0; k < factCount; ++k) {
                    if (facts[k]->factType == "STUDENT_COMPLETED" &&
                        facts[k]->subject == studentID &&
                        facts[k]->object == prereq &&
                        facts[k]->isTrue) {
                        completed = true;
                        break;
                    }
                }

                if (!completed) {
                    cout << "Conflict: student " << studentID
                        << " enrolled in " << courseCode
                        << " without completing " << prereq << endl;
                    ++conflicts;
                }
            }
        }
    }

    if (conflicts == 0)
        cout << "No course conflicts detected.\n";
    else
        cout << "Total course conflicts: " << conflicts << endl;
}

void LogicEngine::detectFacultyConflicts() {
    cout << "\nFACULTY CONFLICT DETECTION\n\n";

    int conflicts = 0;

    for (int i = 0; i < factCount; ++i) {
        if (facts[i]->factType == "FACULTY_TEACHES") {
            string faculty = facts[i]->subject;
            string course = facts[i]->object;

            for (int j = i + 1; j < factCount; ++j) {
                if (facts[j]->factType == "FACULTY_TEACHES" &&
                    facts[j]->object == course &&
                    facts[j]->subject != faculty) {
                    cout << "Conflict: course " << course
                        << " assigned to faculty "
                        << faculty << " and "
                        << facts[j]->subject << endl;
                    ++conflicts;
                }
            }
        }
    }

    if (conflicts == 0)
        cout << "No faculty conflicts detected.\n";
    else
        cout << "Total faculty conflicts: " << conflicts << endl;
}

void LogicEngine::detectLabConflicts() {
    cout << "\nLAB CONFLICT DETECTION\n\n";

    int conflicts = 0;

    for (int i = 0; i < factCount; ++i) {
        if (facts[i]->factType == "LAB_ALLOCATED") {
            string course = facts[i]->subject;
            string lab = facts[i]->object;

            for (int j = i + 1; j < factCount; ++j) {
                if (facts[j]->factType == "LAB_ALLOCATED" &&
                    facts[j]->object == lab &&
                    facts[j]->subject != course) {
                    cout << "Conflict: lab " << lab
                        << " allocated to "
                        << course << " and "
                        << facts[j]->subject << endl;
                    ++conflicts;
                }
            }
        }
    }

    if (conflicts == 0)
        cout << "No lab conflicts detected.\n";
    else
        cout << "Total lab conflicts: " << conflicts << endl;
}

// ======================= automatic rule generation =======================

void LogicEngine::loadDefaultRules() {
    cout << "\nLoading rules from course prerequisites...\n";

    if (!courseSystem) {
        cout << "Course system not attached. No rules generated.\n";
        return;
    }

    int before = ruleCount;

    // For every course, create a PREREQUISITE rule for each prereq:
    // IF STUDENT ENROLLED <course> THEN STUDENT MUST_COMPLETE <prereq>
    for (int i = 0; i < courseSystem->courseCount; ++i) {
        CourseScheduling::Course* c = courseSystem->courses[i];
        for (int j = 0; j < c->prereqCount; ++j) {
            addPrerequisiteRule(c->courseCode, c->prerequisites[j]);
        }
    }

    int added = ruleCount - before;
    cout << "Generated " << added
        << " prerequisite rules from course data.\n";

    // Faculty / lab / time rules can be added explicitly
    // using addFacultyAssignmentRule / addTimeConflictRule
}

void LogicEngine::addPrerequisiteRule(const string& course,
    const string& prerequisite) {
    string condition = "STUDENT ENROLLED " + course;
    string conclusion = "STUDENT MUST_COMPLETE " + prerequisite;
    addRule("PREREQUISITE", condition, conclusion);
}

void LogicEngine::addFacultyAssignmentRule(const string& faculty,
    const string& course,
    const string& lab) {
    string condition = faculty + " TEACHES " + course;
    string conclusion = course + " REQUIRES " + lab;
    addRule("FACULTY_ASSIGNMENT", condition, conclusion);
}

void LogicEngine::addTimeConflictRule(const string& course1,
    const string& course2) {
    // Simple descriptive rule: if a student takes course1, avoid course2
    string condition = "STUDENT ENROLLED " + course1;
    string conclusion = "STUDENT AVOID " + course2;
    addRule("TIME_CONFLICT", condition, conclusion);
}

// ======================= verification helpers =======================

bool LogicEngine::verifyStudentEnrollment(const string& studentID,
    const string& courseCode) {
    return checkFact("STUDENT_ENROLLED", studentID, "ENROLLED_IN", courseCode);
}

bool LogicEngine::verifyFacultyAssignment(const string& facultyID,
    const string& courseCode) {
    return checkFact("FACULTY_TEACHES", facultyID, "TEACHES", courseCode);
}

bool LogicEngine::verifyLabAllocation(const string& courseCode,
    const string& labID) {
    return checkFact("LAB_ALLOCATED", courseCode, "USES_LAB", labID);
}

// ======================= knowledge base display / reports =======================

void LogicEngine::displayKnowledgeBase() {
    cout << "\nKNOWLEDGE BASE\n\n";

    if (kbCount == 0) {
        cout << "Knowledge base is empty.\n";
        return;
    }

    for (int i = 0; i < kbCount; ++i) {
        cout << (i + 1) << ". "
            << knowledgeBase[i][0] << " "
            << knowledgeBase[i][1] << " "
            << knowledgeBase[i][2] << endl;
    }

    cout << "\nTotal entries: " << kbCount << endl;
}

void LogicEngine::generateInferenceReport() {
    cout << "\nINFERENCE ENGINE REPORT\n\n";

    cout << "Rules defined: " << ruleCount << endl;
    cout << "Facts stored: " << factCount << endl;
    cout << "KB entries: " << kbCount << endl;

    int prereqRules = 0;
    int facultyRules = 0;
    int timeRules = 0;
    int otherRules = 0;

    for (int i = 0; i < ruleCount; ++i) {
        if (rules[i]->ruleType == "PREREQUISITE")
            ++prereqRules;
        else if (rules[i]->ruleType == "FACULTY_ASSIGNMENT")
            ++facultyRules;
        else if (rules[i]->ruleType == "TIME_CONFLICT")
            ++timeRules;
        else
            ++otherRules;
    }

    cout << "\nRule breakdown:\n";
    cout << "  Prerequisite rules:  " << prereqRules << endl;
    cout << "  Faculty rules:       " << facultyRules << endl;
    cout << "  Time-conflict rules: " << timeRules << endl;
    cout << "  Other rules:         " << otherRules << endl;
}

// ======================= propositional logic (simple output) =======================

bool LogicEngine::isTautology(const string& proposition) {
    cout << "\nTAUTOLOGY CHECK\n";
    cout << "Proposition: " << proposition << endl << endl;

    string prop = proposition;

    bool hasA = (prop.find('A') != string::npos ||
        prop.find('a') != string::npos);
    bool hasB = (prop.find('B') != string::npos ||
        prop.find('b') != string::npos);

    int numVars = 0;
    if (hasA) ++numVars;
    if (hasB) ++numVars;

    if (numVars == 0) {
        cout << "No propositional variables (A/B) found.\n";
        return false;
    }

    int rows = 1;
    for (int i = 0; i < numVars; ++i) rows *= 2;

    cout << "Variables: ";
    if (hasA) cout << "A ";
    if (hasB) cout << "B ";
    cout << "\nTotal truth assignments: " << rows << "\n\n";

    bool allTrue = true;
    int falseCount = 0;

    for (int i = 0; i < rows; ++i) {
        bool A = false, B = false;

        if (numVars == 1) {
            A = (i == 1);
        }
        else if (numVars == 2) {
            A = (i / 2 == 1);
            B = (i % 2 == 1);
        }

        bool result = false;

        // limited pattern support for demo purposes
        if (prop == "A|!A" || prop == "a|!a") {
            result = A || !A;
        }
        else if (prop == "!(A&!A)" || prop == "!(a&!a)") {
            result = !(A && !A);
        }
        else if (prop == "A->A" || prop == "a->a") {
            result = (!A) || A;
        }
        else if (prop == "A&B" || prop == "a&b") {
            result = A && B;
        }
        else if (prop == "A|B" || prop == "a|b") {
            result = A || B;
        }
        else if (prop == "!A|B" || prop == "!a|b") {
            result = (!A) || B;
        }
        else if (prop == "A" || prop == "a") {
            result = A;
        }
        else {
            cout << "This simple checker supports only basic forms such as:\n";
            cout << "  A|!A , !(A&!A) , A->A , A&B , A|B , !A|B , A\n";
            return false;
        }

        cout << "Row " << (i + 1) << ": ";
        if (hasA) cout << "A=" << (A ? "T" : "F") << " ";
        if (hasB) cout << "B=" << (B ? "T" : "F") << " ";
        cout << "Result=" << (result ? "TRUE" : "FALSE") << endl;

        if (!result) {
            allTrue = false;
            ++falseCount;
        }
    }

    cout << "\nFinal result: ";
    if (allTrue) {
        cout << "the proposition is a tautology.\n";
    }
    else {
        cout << "the proposition is NOT a tautology ("
            << falseCount << " assignment(s) are false).\n";
    }
    cout << endl;

    return allTrue;
}

// ======================= predicate logic =======================

void LogicEngine::addPredicate(const string& name,
    const string& var1,
    const string& var2) {
    if (predicateCount >= predicateCapacity) {
        predicateCapacity *= 2;
        string* temp = new string[predicateCapacity];
        for (int i = 0; i < predicateCount; ++i)
            temp[i] = predicateNames[i];
        delete[] predicateNames;
        predicateNames = temp;
    }

    string predicate = name + "(" + var1;
    if (!var2.empty()) {
        predicate += ", " + var2;
    }
    predicate += ")";

    predicateNames[predicateCount++] = predicate;
    cout << "Predicate defined: " << predicate << endl;
}

void LogicEngine::displayPredicates() {
    cout << "\nPREDICATE DEFINITIONS\n\n";

    if (predicateCount == 0) {
        cout << "No predicates defined.\n";
        return;
    }

    for (int i = 0; i < predicateCount; ++i) {
        cout << (i + 1) << ". " << predicateNames[i] << endl;
    }

    cout << "\nTotal predicates: " << predicateCount << endl;
}

bool LogicEngine::checkPredicate(const string& predicateName,
    const string& arg1,
    const string& arg2) {
    for (int i = 0; i < factCount; ++i) {
        if (facts[i]->predicate == predicateName &&
            facts[i]->subject == arg1) {

            if (arg2.empty() || facts[i]->object == arg2)
                return facts[i]->isTrue;
        }
    }
    return false;
}

bool LogicEngine::universalQuantifier(const string& predicateName,
    string domain[],
    int size) {
    cout << "\nUNIVERSAL QUANTIFIER\n";
    cout << "For all x in domain, " << predicateName << "(x) is true.\n\n";

    bool allTrue = true;

    for (int i = 0; i < size; ++i) {
        bool result = checkPredicate(predicateName, domain[i], "");
        cout << predicateName << "(" << domain[i] << ") = "
            << (result ? "TRUE" : "FALSE") << endl;
        if (!result) allTrue = false;
    }

    cout << "\nOverall result: "
        << (allTrue ? "TRUE" : "FALSE") << endl;
    return allTrue;
}

bool LogicEngine::existentialQuantifier(const string& predicateName,
    string domain[],
    int size) {
    cout << "\nEXISTENTIAL QUANTIFIER\n";
    cout << "There exists x in domain such that "
        << predicateName << "(x) is true.\n\n";

    bool exists = false;

    for (int i = 0; i < size; ++i) {
        bool result = checkPredicate(predicateName, domain[i], "");
        cout << predicateName << "(" << domain[i] << ") = "
            << (result ? "TRUE" : "FALSE") << endl;
        if (result) exists = true;
    }

    cout << "\nOverall result: "
        << (exists ? "TRUE" : "FALSE") << endl;
    return exists;
}
