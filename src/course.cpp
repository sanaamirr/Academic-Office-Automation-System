#include <iostream>
#include <iomanip>
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include <fstream>
using namespace std ; 

course :: course ( string Coursename ,  string courseType ,int credits , double qWeight , double eWeight , double aWeight ) {
this->Coursename = Coursename ; 
this->credits = credits ; 
this->courseType = courseType ; 
this->qWeight = qWeight;
this->eWeight = eWeight;
this->aWeight = aWeight;

    assessments[0] = new Quiz();
    assessments[1] = new Quiz();
    assessments[2] = new Exam();
    assessments[3] = new Exam();
    assessments[4] = new Assignment();
    assessments[5] = new Assignment();
} 
void course :: displayCourseDetails () {
    double grade = this->calculate(); // The logic we fixed earlier
    cout << left << setw(25) << Coursename 
         << setw(10) << courseType 
         << setw(10) << credits 
         << "Grade: " << fixed << setprecision(2) << grade << "%" << endl;
}

double course :: calculate () {
    double final_grade = 0.0 ; 
    for (int i = 0; i < 6; i++) {
    if (assessments[i]) {
        double val = assessments[i]->calculate();
        // cout << "Assessment " << i << " value: " << val << endl;
        final_grade += val;
    }
}
 
    return final_grade;
}
