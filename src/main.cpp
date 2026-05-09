#include <iostream>
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include "../include/Assessment.h"
#include "../include/DatabaseManager.h"
#include "../include/Teacher.h"
#include "../include/Venue.h"
using namespace std ; 
int main () {
// Student s1("s1002", "Sana", "sana@email.com", 3.5, 12, 0, 2 ); 
// course c1 ( "MT1008" , "Multivariable Calculus" , 3 , "Core" , 20.0 , 50.0 , 30.0 );
// s1.add_course(&c1); 
// s1.display() ;
int student_id = 1002 ; 
 DatabaseManager db ;
 db.load_venues() ; 
//  db.load_students() ;
//  cout << "Enter teacher id ";
//  string teacher_id ;
//  cin >> teacher_id;
//  db.load_teachers() ; 
// Teacher * t1 = db.getTeacher (1001); 
//  t1->add_rating(3 , teacher_id);
 //  for ( int i = 0 ; i < 3 ; i++){
//     cout << students[i].display ()  << endl ; 
//  }
// 
//  db.load_weightages() ; 
//  db.load_records(student_id);
//  Student* studentPtr = db.getStudent(student_id); 
//     if (studentPtr != nullptr) {
//         cout << "if statement " << endl ; 
//         studentPtr->calculate() ; 
//         studentPtr->viewTranscript() ; // Now this will have the data loaded by db
//        // studentPtr->display();   
//     } else {
    //     cout << "Student not found in Database!" << endl;
    // }
    // Teacher t1 ( "t2001" , "Dr. Smith" , "dr.smith@email.com" , "Mathematics" , "Multivariable Calculus" );
    // t1.updateRecord("Multivariable Calculus");


//s1.calculate() ; 
}