#include <iostream>
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
using namespace std ;

// using scope resolution operator for definition of class methods 
Student :: Student ( string id , string name  , string email , double gpa  , int cr , int current_count , int max_count ) : AcademicEntity( id , name , email ) {
    this->GPA = gpa ; 
    this->credits = cr ;
    this->current_count = current_count;
    this->max_count = max_count;
    courses = new course [max_count];  
}

void Student :: display () {
    cout << "Student ID : " << this->ID << endl  
    << "Student Name  : " << this->name << endl <<"Student email : " << this->email << endl 
    << "Student GPA : " << this->GPA << endl 
    << "Credit Hours Completed : " << this->credits << endl ;
    cout << "Enrolled Courses : " << endl ;
    for ( int i = 0 ; i < current_count ; i++){
        courses[i].display() ; 
        cout << endl ; 
    }  
}

void Student :: add_course ( course* c ) {

    if ( this->current_count == max_count ){
        cout << "Max Credit hour limit reached. Cannot be enrolled in more courses " << endl ; 
    }
    else {
        if ( this->current_count == 0 ) {
            this->courses = new course [1];
            this->courses [0] = *c ; 
            this->current_count ++ ; 
            cout << "Course added successfully " << endl ;        }
        else {
        course * temp = new course [ this->current_count + 1 ] ;
         for ( int i = 0 ; i < current_count ; i++) {
            temp[i] = this->courses[i] ; 
         }
         temp[this->current_count] = *c ; 
         this->current_count ++ ; 
         delete [] this->courses ; 
         this->courses = new course [ this->current_count ] ; 
         this->courses = temp ; 
        }
    }
}

Student :: ~Student () {
    delete [] this->courses ; 
}
string Student :: get_name () {
    return this->name ; 
}
void Student :: calculate () {
    double total_quality_points = 0.0 ; 
    int total_credits = 0 ; 
    for ( int i = 0 ; i < current_count ; i++){
        cout << "Course: " << courses[i].Coursename << " | Credits: " << courses[i].credits << endl;

        total_quality_points += courses[i].calculate() * courses[i].credits ; 
        total_credits += courses[i].credits ; 
    }
    if ( total_credits > 0 ) {
        double percentage_grade = total_quality_points / total_credits ;
        this->GPA = ( percentage_grade /25.0) ;  
    }
    cout << "GPA calculated successfully. Current GPA is : " << this->GPA << endl ; 
}



