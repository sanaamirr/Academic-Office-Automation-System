#include <iostream>
#include <fstream>  
#include <sstream>   
#include <iostream>  
#include <cstdlib>
using namespace std ;
#include "../include/Student.h"
#include "../include/Course.h" 
#include "../include/DatabaseManager.h"
#include"../include/Assessment.h"


 DatabaseManager :: DatabaseManager () {
     students = new Student *[100] ; 
     for(int i = 0; i < 100; i++) {
        students[i] = nullptr;
    }
    studentCount = 0;
    courses = new course [50];
 }
 void DatabaseManager :: load_students () {
    ifstream input_file("../data/Student.txt");  

    if (!input_file.is_open()) {
        cout << "Error: Could not open " << "data/Student.txt" << endl;
        return;
    }

    string line;
    int studentCount = 0 ; 
    // We stop if we hit the end of file OR our max capacity of 100
 while (getline(input_file, line) && studentCount < 100) {
    if (line.empty()) continue; 

    stringstream ss(line);
    string id, name, email, gpaStr, credStr , type ;

    getline(ss, id,     '|');      
    getline(ss, name,   '|');    
    getline(ss, email,  '|');   
    getline(ss, credStr, '|');
    getline(ss, type, '|');  
    getline(ss, gpaStr);
    
    string cleanType = trim(type);
        if (cleanType == "Scholarship") {
            students[studentCount] = new ScholarshipStudent();
        } else if (cleanType == "Exchange") {
            students[studentCount] = new ExchangeStudent();
        } else {
            students[studentCount] = new RegularStudent();
        }

getline(ss, gpaStr); // This contains "Core:Multivariable Calculus,Elective:Physics"

string cleanCourseList = trim(gpaStr);
stringstream courseSS(cleanCourseList);
string courseEntry;
while (getline(courseSS, courseEntry, ',')) {
    courseEntry = trim(courseEntry); // e.g., "Core:Multivariable Calculus"
    
    size_t colonPos = courseEntry.find(':');
    if (colonPos != string::npos) {
        string type = courseEntry.substr(0, colonPos);
        string name = courseEntry.substr(colonPos + 1);

        // Create a temporary course object
       
        course tempCourse(name, type); 
        // --- CREDIT ASSIGNMENT LOGIC ---
        // We use the 'type' string to set the 'credits' data member
        if (type == "Core") {
            tempCourse.credits = 3;
        } else if (type == "Elective") {
            tempCourse.credits = 2;
        } else if (type == "Lab") {
            tempCourse.credits = 1;
        } else {
            tempCourse.credits = 0; // Safety default
            cout << "Warning: Unknown course type for " << name << endl;
        }

        // Now that credits are set, add it to the student
        students[studentCount]->add_course(&tempCourse);
    }
}
    try {
        students[studentCount]->ID = trim(id);
        students[studentCount]->name = trim(name);
        students[studentCount]->email = trim(email); 
        students[studentCount]->type = cleanType; 
        
        string cleanCred = trim(credStr); 
        if (!cleanCred.empty()) {
            students[studentCount]->credits = stoi(cleanCred);
        }

        
        students[studentCount]->GPA = 0.0; 

        studentCount++; 
    } catch (const std::exception& e) {
        cout << "Parsing Error on Student " << id << ": " << e.what() << endl;
    }
}
    input_file.close();
    cout << "Students loaded successfully " << endl ; 
 }
 void DatabaseManager :: load_weightages () {
    cout << "Loading weightages  "  << endl ; 
    ifstream course_file ("../data/Courses.txt");
    if (!course_file.is_open()) {
        cout << "Error: could not open " << "Courses.txt" << endl;
        return;
    }
    else {
        cout << "Courses file opened successfully" << endl ; 
    }
int weightageCount = 0 ; 
    string line;
    while (getline(course_file, line) && weightageCount < 3 ) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, examW, assignW, quizW;

        getline(ss, type,   '|');
        getline(ss, examW,  '|');
        getline(ss, assignW,'|');
        getline(ss, quizW,  '|');

      try {
            
            weightage[weightageCount].courseType = trim(type);
            
            // 2. TRIM BEFORE STOD - This is the most likely crash site
            string cleanExam = trim(examW);
            string cleanAssign = trim(assignW);
            string cleanQuiz = trim(quizW);

            if(!cleanExam.empty()) weightage[weightageCount].examW = stod(cleanExam);
            if(!cleanAssign.empty()) weightage[weightageCount].assignW = stod(cleanAssign);
            if(!cleanQuiz.empty()) weightage[weightageCount].quizW = stod(cleanQuiz);

            weightageCount++;
        } catch (...) {
            cout << "Skipping invalid weightage line for: " << type << endl;
        }
    }
    cout << "Weightages loaded successfully " << endl ; 
    course_file.close();
 }
string DatabaseManager ::  trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
int  DatabaseManager :: findStudentIndexByID ( int student_id ) {
    for ( int i = 0 ; i < 100 ; i ++ ) {
        if ( students[i]->ID == "s" + to_string ( student_id ) ) {
            return i ; 
        }        
    }
    return -1 ; 
}
Student* DatabaseManager :: getStudent ( int student_id ) {
    int idx = findStudentIndexByID(student_id ) ;
    if ( idx!= -1 ) {
        cout << "Student found " << endl ; 
        return students[idx] ; }
else {
    cout << "Student not found " << endl ; 
    return nullptr ; 
}
}
void DatabaseManager :: load_records (int student_id ) {
    cout << "loading " << endl ; 
// 1. Find the student in your database array
    int sIdx = findStudentIndexByID(student_id);
    if (sIdx == -1) return; 

    Student* currentStudent = students[sIdx];

    // 2. Loop through each course the student is taking
    cout << "Loading records for: " << currentStudent->name 
         << " | Courses found: " << currentStudent->current_count << endl;
    load_weightages(); 
    for (int i = 0; i < currentStudent->current_count; i++) {
        course* currentCourse = &currentStudent->courses[i];
        
        for ( int j = 0 ; j < 3 ; j++ ) {
            if ( weightage[j].courseType == currentCourse->courseType ) {
                currentCourse->qWeight = weightage[j].quizW;
                currentCourse->eWeight = weightage[j].examW;
                currentCourse->aWeight = weightage[j].assignW;
            }
        } 

        // --- STEP B: OPEN THE STUDENT'S RECORD FILE ---
       string folderPath = "../data/"; 
string fileName = folderPath + trim(currentCourse->Coursename) + ".txt"; // Ensure name is "Multivariable Calculus"

ifstream recordFile(fileName);
        if (!recordFile.is_open()) {
            cout << "error opening record file " << endl ;  
        continue ;        }
        else {
            cout << "opening record file " << endl ;         }

        string line;
     //   getline(recordFile, line); // Skip the course name header

        // --- STEP C: SEARCH FOR THE STUDENT ID ---
       while (getline(recordFile, line)  )  {
    if (line.empty()) continue;
    cout << "Reading line : " << line << endl ; 

    stringstream ss(line);
    string idStr, nameStr;

    // 1. Read the ID (e.g., s1002)
    getline(ss, idStr, '|');
    idStr = trim(idStr);

    // 2. Read the Name (e.g., Sana) and DISCARD it
    // We don't need it because we already have the student object
    getline(ss, nameStr, '|');

    // 3. Compare IDs
    // Assuming student_id is an int like 1002, we compare it to "s1002"
    cout << "ID" << idStr << endl ; 
    if (idStr == "s" + to_string(student_id)) {
        cout << "Found student record for ID: " << idStr << endl;
        // These are the max marks and weights you defined earlier
        double max_vals[6] = {10, 10, 50, 50, 20, 20};
        double weights[6] = {
            currentCourse->qWeight/2, currentCourse->qWeight/2, 
            currentCourse->eWeight/2, currentCourse->eWeight/2, 
            currentCourse->aWeight/2, currentCourse->aWeight/2
        };
        for ( int i = 0 ; i < 6 ; i++ ) {
            cout << "Weights " << endl ;
            cout << weights[i] << endl ; 
        }

        // 4. Read the 6 scores
        for (int k = 0; k < 6; k++) {
            string scoreStr;
            if (getline(ss, scoreStr, '|')) {
                string cleanScore = trim(scoreStr);
                
                // Safety check: make sure it's not empty before converting
                if (!cleanScore.empty()) {
                    try {
                        double raw = stod(cleanScore);
                        currentCourse->assessments[k]->set_data(raw, max_vals[k], weights[k]);
                    } catch (...) {
                        cout << "Warning: Invalid score [" << cleanScore << "] for student " << idStr << endl;
                    }
                }
            }
        }
        break; // Found the student, no need to keep reading this file
    }
    else {
        cout << "Student not found in record " << fileName << endl ; 
    }
}
        recordFile.close() ; }
}
void DatabaseManager::generateTranscript(int targetID) {
    // 1. FIND the student
    Student* s = getStudent(targetID); 
    
    if (s != nullptr) {
        // 2. LOAD the data from the files (The logic you just fixed!)
        load_records(targetID); 
        
        // 3. CALCULATE the final GPA
        s->calculate(); 
        
        // 4. DISPLAY the result
        s->viewTranscript(); 
    } else {
        cout << "Error: Student not found in database." << endl;
    }
}
DatabaseManager::~DatabaseManager() {
    for (int i = 0; i < studentCount; i++) {
        delete students[i]; // Delete each individual student
    }
    delete[] students; // Delete the array of pointers
    delete[] courses;
}
