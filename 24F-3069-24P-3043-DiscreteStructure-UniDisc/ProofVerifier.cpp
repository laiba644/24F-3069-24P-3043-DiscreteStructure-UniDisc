#include "ProofVerifier.h"
#include <iostream>
using namespace std;

// ---------- Constructor ----------
ProofVerifier::ProofVerifier(CourseScheduling* s, InductionChecker* i, LogicEngine* l, UniversityDatabase* d) {
    sys = s;
    indu = i;
    logic = l;
    db = d;
    
  
}

// ---------- Utility: Sort prerequisite chain ----------
void ProofVerifier::sortChain(string arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// ---------- Induction Proof ----------
void ProofVerifier::proveCourseEligibility(const string& course, string completed[], int cCount) {
    cout << "\n=== FORMAL INDUCTION PROOF OF ELIGIBILITY FOR " << course << " ===\n";

    string chain[200];
    int count = 0;
    indu->getFullChain(course, chain, count);

    if (count == 0) {
        cout << "No prerequisites -> Trivially True.\n";
        return;
    }

    sortChain(chain, count);

    cout << "\nStep 1 : Basis Case\n";
    cout << "Check smallest prerequisite: " << chain[0] << endl;

    bool basis = false;
    for (int i = 0; i < cCount; i++)
        if (completed[i] == chain[0])
            basis = true;

    cout << (basis ? " Basis holds\n" : " Basis fails\n");

    cout << "\nStep 2 : Inductive Step\n";

    bool ok = true;
    for (int i = 0; i < count; i++) {
        bool has = false;
        for (int j = 0; j < cCount; j++)
            if (chain[i] == completed[j])
                has = true;
        cout << "Does student have " << chain[i] << "?  "
            << (has ? "\n" : "\n");
        if (!has) ok = false;
    }

    cout << "\nConclusion:\n";
    cout << (ok ? " Student MAY take " : " Student may NOT take ");
    cout << course << "\n";
}

// ---------- Verify Specific Rule ----------
void ProofVerifier::proveLogicRule(int index) {
    cout << "\n=== LOGIC RULE #" << index + 1 << " PROOF ===\n";
    logic->enableRule(index);
    logic->forwardChaining();
}

// ---------- Relational Consistency ----------
void ProofVerifier::proveFacultyLabConsistency(const string& course) {
    cout << "\n=== RELATIONAL CONSISTENCY PROOF FOR " << course << " ===\n";

    string faculty = db->getFacultyOfCourse(course);
    string lab = db->getLabOfCourse(course);
    if (faculty == "" || lab == "") {
        cout << " Warning: Database has no record for faculty or lab mapping for this course.\n";
    }
    bool f = logic->verifyFacultyAssignment(faculty, course);
    bool l = logic->verifyLabAllocation(course, lab);

    cout << "Faculty Assigned?       " << (f ? " Yes\n" : " No\n");
    cout << "Correct Lab Allocated?  " << (l ? " Yes\n" : " No\n");

    cout << "\nConclusion: ";
    cout << ((f && l) ? " Mapping Consistent\n" : " Mapping Inconsistent\n");
}

