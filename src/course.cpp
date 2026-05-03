#include <iostream>
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
void course :: display () {
cout << this->Coursename << endl << 
this->credits << endl ;  
}
// reading the assessment data from the course file 
// ifstream course_file ("Course.txt");
// int no_of_assessments = 0; 
// string assessment ;
// double qWeight , aWeight , eWeight ; 
// while ( course_file >> assessment ) {
//     if ( assessment == "Quiz"){
//     course_file >>qNum >> qWeight ; 
// }
//     else if (assessment == "Assignment"){
//         course_file >>aNum >>aWeight ; 
//     }
//      else if (assessment == "Exam"){
//         course_file >>eNum >>eWeight ; 
//     }
// }
// no_of_assessments = qNum + aNum + eNum ; 

double course :: calculate () {
    double final_grade = 0.0 ; 
    for (int i = 0; i < 6; i++) {
    if (assessments[i]) {
        double val = assessments[i]->calculate();
        cout << "Assessment " << i << " value: " << val << endl;
        final_grade += val;
    }
}
 
    return final_grade;
}
