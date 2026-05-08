#include <iostream>
#include <iomanip>
#include <fstream>
#include"../include/DatabaseManager.h"
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include "../include/Teacher.h"
using namespace std ;

// using scope resolution operator for definition of class methods 
Student :: Student ( string id , string name  , string email , double gpa  , int cr , string type , int current_count , int max_count ) : AcademicEntity( id , name , email ) {
    this->GPA = gpa ; 
    this->credits = cr ;
    this->type = type ;
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
       // courses[i].displayCourseDetails() ; 
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

        total_quality_points += courses[i].calculate() * courses[i].credits ; 
        total_credits += courses[i].credits ; 
    }
    if ( total_credits > 0 ) {
        double percentage_grade = total_quality_points / total_credits ;
        this->GPA = ( percentage_grade /25.0) ;  
    }
    cout << "GPA calculated successfully. Current GPA is : " << this->GPA << endl ; 
}
void Student::viewTranscript() {
    cout << "============================================" << endl;
    cout << "           ACADEMIC TRANSCRIPT              " << endl;
    cout << "============================================" << endl;
    cout << "Name: " << name << " | ID: " << ID << endl;
    cout << "--------------------------------------------" << endl;
    cout << left << setw(25) << "Course Name" << setw(10) << "Type" << setw(10) << "Credits" << "Score" << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < current_count; i++) {
        courses[i].displayCourseDetails();
    }

    cout << "--------------------------------------------" << endl;
    cout << "Final GPA: " << fixed << setprecision(2) << GPA << endl;
    cout << "============================================" << endl;
}
void RegularStudent::viewTranscript() {
 Student :: viewTranscript() ; 
   
}
void ExchangeStudent::viewTranscript() {
    cout << "--- EXCHANGE STUDENT TRANSCRIPT (PASS/FAIL) ---" << endl;
    cout << "Name: " << name << " | ID: " << ID << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < current_count; i++) {
        double grade = courses[i].calculate();
        string status = (grade >= 50.0) ? "PASS" : "FAIL";
        
        cout << left << setw(25) << courses[i].Coursename 
             << "Status: " << status << " (Credits: " << courses[i].credits << ")" << endl;
    }
    cout << "--------------------------------------------" << endl;
    cout << "Overall Result: " << (GPA >= 2.0 ? "TRANSFERRED" : "NOT TRANSFERRED") << endl;
}
void ScholarshipStudent::viewTranscript() {
    Student:: calculate () ; 
    Student::viewTranscript(); 
    cout << "--- SCHOLARSHIP STATUS ---" << endl;
    
    if (GPA < 3.0) {
        cout << "WARNING: Your GPA is " << GPA << "." << endl;
        cout << "STATUS: PROBATION" << endl;
        cout << "Action Required: Contact Academic Advisor immediately." << endl;
    } else {
        cout << "STATUS: ACTIVE" << endl;
        cout << "Congratulations, your scholarship is in good standing." << endl;
    }
    cout << "============================================" << endl;
}
// void Student :: add_rating( double score  , string teacher_id ){
//     if (score< 1 || score > 5) {
//         cout << "Error: Rating must be between 1 and 5." << endl;
//         return;
//     }  
//     ifstream file("../data/Teacher.txt");
//     ofstream temp("../data/temp.txt");
//     string line;
//     bool found = false;

//     while (getline(file, line)) {
//         if (line.find(teacher_id) != string::npos) {
//             found = true;
//             stringstream ss(line);
//             string id, name, email, dept, subject, ratingCount, rating;

//             // 2. Parse the existing data (Assumes: ID | Name | Email | Dept | Sub | Sum | Count)
//             getline(ss, id, '|');
//             getline(ss, name, '|');
//             getline(ss, email, '|');
//             getline(ss, dept, '|');
//             getline(ss, subject, '|');
//             getline(ss, ratingCount, '|');
//             getline(ss, rating, '|');

//             // 3. Apply the Formula
//             // assuming that we will load a teachers array also 
//             this->rating_count ++ ; 
//              if ( this->rating_count  == 1  ){
//                    this->total_ratingSum = score ;
//              }
//              else {
//                 this->total_ratingSum = this->total_ratingSum + ( score - this->total_ratingSum) / this->rating_count;
//              }
         

//             // 4. Reconstruct the line with updated stats
//             // We use fixed/setprecision to keep the file looking clean
//             stringstream updated;
//             updated << id << "|" << name << "|" << email << "|" << dept << "|" << subject << "|" 
//                     << fixed << setprecision(1) << ratingCount << "|" << rating  << "|";
            
//             temp << updated.str() << endl;
//         } else {
//             temp << line << endl;
//         }
//     }

//     file.close();
//     temp.close();

//     remove("../data/Teacher.txt");
//     rename("../data/temp.txt", "../data/Teacher.txt");

//     if (found) cout << "Rating submitted! New Average: " << endl;
//     else cout << "Teacher ID not found." << endl;
// }