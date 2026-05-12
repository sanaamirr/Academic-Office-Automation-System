#include <iostream>
#include <iomanip>
#include <fstream>
#include"../include/DatabaseManager.h"
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include "../include/Teacher.h"
#include "../include/Classes.h"
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

void Student::add_course(course* c) {
    // 1. Create a bigger array
    course* temp = new course[this->current_count + 1];
    
    // 2. Copy old courses
    for (int i = 0; i < current_count; i++) {
        temp[i] = this->courses[i];
    }

    // 3. Add the new one
    temp[current_count] = *c;
    
    // 4. Update pointer and count
    delete[] this->courses;
    this->courses = temp;
    this->current_count++;
}
void Student::add_course(Classes** catalog, int catalogCount, string targetID) {
    
    // 1. LIMIT CHECK
    if (this->current_count == max_count) {
        cout << "Max Credit hour limit reached!" << endl;
        return;
    }

    // 2. AUTO-FILL LOGIC (Find details from catalog)
    Classes* foundTemplate = nullptr;
    for (int i = 0; i < catalogCount; i++) {
        if (catalog[i] != nullptr && catalog[i]->courseID == targetID) {
            foundTemplate = catalog[i];
            break;
        }
    }

    if (!foundTemplate) {
        cout << "Course ID " << targetID << " not found in catalog!" << endl;
        return;
    }

    // 3. MEMORY UPDATE (Resize your array)
    course* temp = new course[this->current_count + 1];
    for (int i = 0; i < current_count; i++) {
        temp[i] = this->courses[i];
    }

    // Fill the new course object with details from the catalog
    temp[current_count].courseID = foundTemplate->courseID;
    temp[current_count].Coursename = foundTemplate->courseName;
    temp[current_count].courseType = foundTemplate->type;
    temp[current_count].credits = (foundTemplate->type == "Core") ? 3 : 2;

    delete[] this->courses;
    this->courses = temp; // Point to the new larger array
    this->current_count++;

    // 4. FILE PERSISTENCE (Update Student.txt)
   // 4. FILE PERSISTENCE (Update Student.txt)
ifstream inFile("../data/Student.txt");
ofstream outFile("../data/temp.txt");
string line;

if (!inFile.is_open() || !outFile.is_open()) {
    cerr << "Error: Could not open student files for updating!" << endl;
    return;
}

while (getline(inFile, line)) {
    if (line.empty()) continue;

    // Check if this line belongs to the current student
    if (line.find(this->ID) != string::npos) {
        
        // Step A: Find the last pipe '|' where the courses list starts
        size_t lastPipe = line.find_last_of('|');
        if (lastPipe == string::npos) {
            // If no pipe is found, something is wrong with the file format
            outFile << line << endl;
            continue;
        }

        // Step B: Split the line into the Info part and the Courses part
        string baseInfo = line.substr(0, lastPipe + 1); // Up to the last '|'
        string existingCourses = line.substr(lastPipe + 1);

        // Step C: Clean up any hidden spaces or newlines
        existingCourses.erase(0, existingCourses.find_first_not_of(" \t\r\n"));
        size_t lastChar = existingCourses.find_last_not_of(" \t\r\n");
        if (lastChar != string::npos) {
            existingCourses = existingCourses.substr(0, lastChar + 1);
        } else {
            existingCourses = ""; // It was just whitespace
        }

        // Step D: Create the new entry (Format: Type:Name)
        string newEntry = foundTemplate->type + ":" + foundTemplate->courseName;

        // Step E: Combine everything back together
        string updatedLine;
        if (existingCourses.empty()) {
            // If this is the first course being added
            updatedLine = baseInfo + " " + newEntry;
        } else {
            // If courses already exist, add a comma
            updatedLine = baseInfo + " " + existingCourses + "," + newEntry;
        }

        outFile << updatedLine << endl;
    } else {
        // Not the student we are looking for, keep the line as is
        outFile << line << endl;
    }
}

inFile.close();
outFile.close();

// Final Step: Replace the old file
remove("../data/Student.txt");
rename("../data/temp.txt", "../data/Student.txt");

cout << "File updated successfully for student " << this->ID << endl;

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