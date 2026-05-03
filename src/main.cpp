#include <iostream>
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include "../include/Assessment.h"
#include "../include/DatabaseManager.h"
using namespace std ; 
int main () {
// Student s1("s1002", "Sana", "sana@email.com", 3.5, 12, 0, 2 ); 
// course c1 ( "MT1008" , "Multivariable Calculus" , 3 , "Core" , 20.0 , 50.0 , 30.0 );
// s1.add_course(&c1); 
// s1.display() ;
DatabaseManager db ;
db.load_students() ;
int student_id = 1002 ; 




 db.load_weightages() ; 
 db.load_records(student_id);
 Student* studentPtr = db.getStudent(student_id); 
    if (studentPtr != nullptr) {
        cout << "if statement " << endl ; 
        studentPtr->calculate() ; 
        studentPtr->viewTranscript() ; // Now this will have the data loaded by db
       // studentPtr->display();   
    } else {
        cout << "Student not found in Database!" << endl;
    }
//s1.calculate() ; 
}