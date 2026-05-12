#include <iostream>
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include "../include/Assessment.h"
#include "../include/DatabaseManager.h"
#include "../include/Teacher.h"
#include "../include/Venue.h"
#include "../include/Scheduler.h"
using namespace std ; 

int main () {
DatabaseManager db;
    Scheduler sc;

db.load_students ();
db.load_teachers () ; 
db.load_weightages (); 
db.load_venues () ; 
db.load_courses() ;


    int role = 0;

    while (true) {
        cout << "\n======================================" << endl;
        cout << "   UNIVERSITY MANAGEMENT SYSTEM" << endl;
        cout << "======================================" << endl;
        cout << "1. Enter as Student" << endl;
        cout << "2. Enter as Teacher" << endl;
        cout << "3. Enter as Admin" << endl;
        cout << "4. Exit" << endl;
        cout << "Select Role: ";
        cin >> role;
        if (role == 4)break;
        if (role == 1) { 
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            int numericID = stoi (id.substr(1));
            Student* currentStudent = db.getStudent(numericID);
            if (currentStudent != nullptr) {
                cout << "Welcome, " << currentStudent->get_name() << "!" << endl;
    
                int action;
                cout << "1. View Transcript  2. Register Course\nAction: ";
                cin >> action;

                if (action == 1){ 
                    db.load_records(numericID);
                    currentStudent->viewTranscript();}
                else if (action == 2) {
                    string cID;
                    cout << "Enter Course ID: ";
                    cin >> cID;
                     int i  = db.findCourseByID(cID);
                     cout << "The id has been found " << i << endl ; 
                    //cout << "Temp : " << i; 
                    currentStudent->add_course(db.classes , 2 , cID);
                }
            }
             else {
                cout << "Error: Student ID not found." << endl;
            }}}

     
    return 0;

}