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
#include "../include/Venue.h"
#include "../include/Classes.h"
 DatabaseManager :: DatabaseManager () {
     students = new Student *[100] ; 
     for(int i = 0; i < 100; i++) {
        students[i] = nullptr;
    }
    studentCount = 0;
    teachers = new Teacher *[20];
    for(int i = 0; i < 20; i++) {
        teachers[i] = nullptr;
    }
    teacherCount = 0 ; 
      venues = new Venue *[20];
    for(int i = 0; i < 20; i++) {
        venues[i] = nullptr;
    }
    venueCount  = 0 ; 
    courses = new course [50];
    classes = new Classes *[20];
    for(int i = 0; i < 20; i++) {
        classes[i] = nullptr;
    }
    classescount  = 0 ; 
 }
// void DatabaseManager :: load_students () {
//     ifstream input_file("../data/Student.txt");  

//     if (!input_file.is_open()) {
//         cout << "Error: Could not open " << "data/Student.txt" << endl;
//         return;
//     }

//     string line;
//     int studentCount = 0 ; 
//     // We stop if we hit the end of file OR our max capacity of 100
//  while (getline(input_file, line) && studentCount < 100) {
//     if (line.empty()) continue; 

//     stringstream ss(line);
//     string id, name, email, gpaStr, credStr , type ;

//     getline(ss, id,     '|');      
//     getline(ss, name,   '|');    
//     getline(ss, email,  '|');   
//     getline(ss, credStr, '|');
//     getline(ss, type, '|');  
//     getline(ss, gpaStr);
    
//     string cleanType = trim(type);
//         if (cleanType == "Scholarship") {
//             students[studentCount] = new ScholarshipStudent();
//         } else if (cleanType == "Exchange") {
//             students[studentCount] = new ExchangeStudent();
//         } else {
//             students[studentCount] = new RegularStudent();
//         }

// getline(ss, gpaStr); 

// string cleanCourseList = trim(gpaStr);
// stringstream courseSS(cleanCourseList);
// string courseEntry;
// while (getline(courseSS, courseEntry, ',')) {
//     courseEntry = trim(courseEntry); 
    
//     size_t colonPos = courseEntry.find(':');
//     if (colonPos != string::npos) {
//         string type = courseEntry.substr(0, colonPos);
//         string name = courseEntry.substr(colonPos + 1);

//         course tempCourse(name, type); 

//         if (type == "Core") {
//             tempCourse.credits = 3;
//         } else if (type == "Elective") {
//             tempCourse.credits = 2;
//         } else if (type == "Lab") {
//             tempCourse.credits = 1;
//         } else {
//             tempCourse.credits = 0; 
//             cout << "Warning: Unknown course type for " << name << endl;
//         }

//         students[studentCount]->add_course(&tempCourse);
//     }
// }
//     try {
//         students[studentCount]->ID = trim(id);
//         students[studentCount]->name = trim(name);
//         students[studentCount]->email = trim(email); 
//         students[studentCount]->type = cleanType; 
        
//         string cleanCred = trim(credStr); 
//         if (!cleanCred.empty()) {
//             students[studentCount]->credits = stoi(cleanCred);
//         }

        
//         students[studentCount]->GPA = 0.0; 

//         studentCount++; 
//     } catch (const std::exception& e) {
//         cout << "Parsing Error on Student " << id << ": " << e.what() << endl;
//     }
// }
//     input_file.close();
//     cout << "Students loaded successfully " << endl ; 
//  }
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
void DatabaseManager :: load_teachers () {
string filename = "../data/Teacher.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open teacher file!" << endl;
        return;
    }
    else {
        cout << "File has been opened successfully " << endl ; 
    }

    string line;
    int index = 0;
    int max = 20 ; 

    // Read file line by line
    while (getline(file, line) && index < max ) {
 cout << "File is being read" << endl ; 
        if (line.empty()){
            cout << "reading empty lines "<< endl ; 
         break ; }


        stringstream ss(line);
        string id, name, email, dept, subject, ratingStr, countStr;

        // 1. Extract data using the pipe '|' delimiter
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, email, '|');
        getline(ss, dept, '|');
        getline(ss, subject, '|');
        getline(ss, ratingStr, '|'); 
        getline(ss, countStr, '|');  
         cout << id << name << email << endl ; 
        double loadedRating = (ratingStr == "" || ratingStr == " ") ? 0.0 : stod(ratingStr);
        int loadedCount = (countStr == "" || countStr == " ") ? 0 : stoi(countStr);

        cout << "Putting away the data " << endl ; 
        if ( teachers[index] == nullptr ){
            teachers[index] = new Teacher () ; 
        }
      teachers[index]->ID = id;
teachers[index]->name = name;
teachers[index]->email = email;
teachers[index]->department = dept;
teachers[index]->subject = subject;
teachers[index]->total_ratingSum = loadedRating; 
teachers[index]->rating_count = loadedCount;

        index++;
        cout << "Index" << endl ; 
    }
cout << "It is here " << endl ; 
    this->teacherCount = index; 
    file.close();
    cout << "Successfully loaded " << teacherCount << " teachers." << endl;
}
void DatabaseManager :: load_venues () {
    string filename = "../data/Venues.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open venue file!" << endl;
        return;
    }
    string line;
    int index = 0;
    int maxVenues = 20; 

    while (getline(file, line) && index < maxVenues) {
        
        if (line.empty()) continue;

        stringstream ss(line);
        string id, capStr, compStr, slotsStr;

        // 1. Extract data using '|'
        getline(ss, id, '|');     
        getline(ss, capStr, '|');  
        getline(ss, compStr, '|'); 
        getline(ss, slotsStr, '|'); 

        // 2. Memory Safety: Double Pointer Check
        if (venues[index] == nullptr) {
             venues[index] = new Venue();
        }

        // 3. Simple Assignments
        venues[index]->roomID = id;
        venues[index]->capacity = (capStr == "" || capStr == " ") ? 0 : stoi(capStr);
        venues[index]->hasComputers = (compStr == "1");

        stringstream slotSS(slotsStr);
        string singleSlot;
        int slotIndex = 0;
        
        while (getline(slotSS, singleSlot, ',') && slotIndex < 3) {
            venues[index]->isBooked[slotIndex] = (singleSlot == "1");
            slotIndex++;
        }

        index++;
    }

    this->venueCount = index;
    file.close(); 
    cout << "Successfully loaded " << venueCount << " venues." << endl;
   
}
// this is loading classes.txt
void DatabaseManager :: load_courses () {
    ifstream file("../data/Classes.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open " << endl;
        return;
    }

    string line;
    int index = 0;

    // if (this->classesArray == nullptr) {
    //     this->classesArray = new Classes*[100]; 
    // }

   while (getline(file, line) && index < 20) {
    if (line.empty()) continue;
    stringstream ss(line);
    string id, name, type, temp;

    getline(ss, id, '|');   // Now "MT1008"
    getline(ss, name, '|'); // Now "Multivariable Calculus"
    
    getline(ss, temp, '|');
    int count = stoi(temp);
    
    getline(ss, type, '|'); // Now "Core" (No ghost spaces!)
    
    getline(ss, temp, '|');
    bool assigned = (stoi(temp) != 0);

    classes[index] = new Classes(id, name, count, type, assigned);
    index++;
}

}
void DatabaseManager::load_students() {
    ifstream input_file("../data/Student.txt");
    if (!input_file.is_open()) {
        cout << "Error: Could not open data/Student.txt" << endl;
        return;
    }

    string line;
    int studentCount = 0;
    while (getline(input_file, line) && studentCount < 100) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, email, credStr, typeStr, courseList;

        // 1. Parse the fixed columns
        getline(ss, id,      '|');
        getline(ss, name,    '|');
        getline(ss, email,   '|');
        getline(ss, credStr, '|');
        getline(ss, typeStr, '|'); // This gets "Regular", "Scholarship", etc.
        
        // 2. Parse the rest of the line (The Courses)
        getline(ss, courseList); 

        // 3. Create the correct Student object type
        string cleanType = trim(typeStr);
        if (cleanType == "Scholarship") {
            students[studentCount] = new ScholarshipStudent();
        } else if (cleanType == "Exchange") {
            students[studentCount] = new ExchangeStudent();
        } else {
            students[studentCount] = new RegularStudent();
        }

        // 4. Populate Student Basic Info
        students[studentCount]->ID = trim(id);
        students[studentCount]->name = trim(name);
        students[studentCount]->email = trim(email);
        students[studentCount]->type = cleanType;
        
        try {
            string cleanCred = trim(credStr);
            students[studentCount]->credits = (!cleanCred.empty()) ? stoi(cleanCred) : 0;
        } catch (...) { students[studentCount]->credits = 0; }

        // 5. Parse the Course List (Core:Multivariable Calculus, Core:LinearAlgebra)
        stringstream courseSS(courseList);
        string courseEntry;
        while (getline(courseSS, courseEntry, ',')) {
            courseEntry = trim(courseEntry);
            if (courseEntry.empty()) continue;

            size_t colonPos = courseEntry.find(':');
            if (colonPos != string::npos) {
                string cType = trim(courseEntry.substr(0, colonPos));
                string cName = trim(courseEntry.substr(colonPos + 1));

                course tempCourse;
                tempCourse.Coursename = cName;
                tempCourse.courseType = cType;

                // Assign credits based on type
                if (cType == "Core") tempCourse.credits = 3;
                else if (cType == "Elective") tempCourse.credits = 2;
                else if (cType == "Lab") tempCourse.credits = 1;

                // Add to the student's internal array
                students[studentCount]->add_course(&tempCourse);
            }
        }
        studentCount++;
    }
    input_file.close();
    cout << "Students and their courses loaded successfully!" << endl;
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
int  DatabaseManager :: findTeacherIndexByID ( int teacher_id ) {
    for ( int i = 0 ; i < 20 ; i ++ ) {
        if ( teachers[i]->ID == "t" + to_string ( teacher_id ) ) {
            return i ; 
        }        
    }
    return -1 ; 
}
int DatabaseManager :: findCourseByID ( string course_id){
    for ( int i = 0 ; i < 10 ; i++){
        if ( classes[i] != nullptr ){
            cout << "Comparing: [" << classes[i]->courseID << "] with [" << course_id << "]" << endl;
        if ( classes[i]->courseID == course_id ){
            return i;
        }}
    }
    cout << "Course is not found " << endl ;
    return -1;
}
Teacher* DatabaseManager :: getTeacher ( int teacher_id ) {
    int idx = findTeacherIndexByID(teacher_id ) ;
    if ( idx!= -1 ) {
        cout << "Teacher found " << endl ; 
        return teachers[idx] ; }
else {
    cout << "Teacher not found " << endl ; 
    return nullptr ; 
}
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
Classes * DatabaseManager ::  getCourse (string course_id ){
    int idx = findCourseByID(course_id ) ;
    if ( idx!= -1 ) {
        cout << "Course found " << endl ; 
        return classes[idx] ; }
else {
    cout << "Course not found " << endl ; 
    return nullptr ; 
} 
}
void DatabaseManager::load_records(int student_id) {
    cout << "--- Starting Record Load ---" << endl;

    // 1. Locate the student in the database
    int sIdx = findStudentIndexByID(student_id);
    if (sIdx == -1) {
        cout << "Error: Student ID s" << student_id << " not found." << endl;
        return;
    }

    Student* currentStudent = students[sIdx];
    string targetID = "s" + to_string(student_id);

    cout << "Loading " << currentStudent->current_count << " courses for " << currentStudent->name << endl;
    
    // Ensure weightages are loaded for the current session
    load_weightages(); 

    // OUTER LOOP: Iterate through every course currently in the student's array
    for (int i = 0; i < currentStudent->current_count; i++) {
        course* currentCourse = &currentStudent->courses[i];
        
        // Step A: Assign weights to the course based on its Type (Core/Lab/Elective)
        for (int j = 0; j < 3; j++) {
            if (weightage[j].courseType == currentCourse->courseType) {
                currentCourse->qWeight = weightage[j].quizW;
                currentCourse->eWeight = weightage[j].examW;
                currentCourse->aWeight = weightage[j].assignW;
            }
        }

        // Step B: Open the specific Course Record File
        string cleanName = trim(currentCourse->Coursename);
        string fileName = "../data/" + cleanName + ".txt";
        cout << fileName << endl ; 
        ifstream recordFile(fileName);
        if (!recordFile.is_open()) {
            cout << "Notice: Skipping file [" << fileName << "] (Not found)" << endl;
            continue; // Move to the next course if file is missing
        }

        string line;
        bool studentFoundInFile = false;

        // INNER LOOP: Search for the student ID within the course-specific file
        while (getline(recordFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string idStr, dummyName;

            // Extract ID and skip the Name column
            getline(ss, idStr, '|');
            idStr = trim(idStr);
            getline(ss, dummyName, '|'); 

            if (idStr == targetID) {
                // Calculation constants for scaling scores
                double max_vals[6] = {10, 10, 50, 50, 20, 20};
                double weights[6] = {
                    currentCourse->qWeight/2, currentCourse->qWeight/2, 
                    currentCourse->eWeight/2, currentCourse->eWeight/2, 
                    currentCourse->aWeight/2, currentCourse->aWeight/2
                };

                // Read the 6 score columns (2 Quizzes, 2 Exams, 2 Assignments)
                for (int k = 0; k < 6; k++) {
                    string scoreStr;
                    if (getline(ss, scoreStr, '|')) {
                        string cleanScore = trim(scoreStr);
                        
                        if (!cleanScore.empty()) {
                            try {
                                // IMPORTANT: Instantiate concrete types as Assessment is abstract
                                if (currentCourse->assessments[k] == nullptr) {
                                    if (k < 2)      currentCourse->assessments[k] = new Quiz();
                                    else if (k < 4) currentCourse->assessments[k] = new Exam();
                                    else            currentCourse->assessments[k] = new Assignment();
                                }
                                
                                double raw = stod(cleanScore);
                                // Polmorphic call to set data
                                currentCourse->assessments[k]->set_data(raw, max_vals[k], weights[k]);
                                
                            } catch (...) {
                                cout << "Warning: Bad data in " << fileName << " for student " << targetID << endl;
                            }
                        }
                    }
                }
                studentFoundInFile = true;
                break; // Exit the 'while' loop for the current file
            }
        }
        recordFile.close();

        if (!studentFoundInFile) {
            cout << "Info: ID " << targetID << " has no entry in " << fileName << endl;
        }
    }
    cout << "--- Record Load Complete ---" << endl;
}
// void DatabaseManager :: load_records (int student_id ) {
//     cout << "loading " << endl ; 
// // 1. Find the student in your database array
//     int sIdx = findStudentIndexByID(student_id);
//     if (sIdx == -1) return; 

//     Student* currentStudent = students[sIdx];

//     // 2. Loop through each course the student is taking
//     cout << "Loading records for: " << currentStudent->name 
//          << " | Courses found: " << currentStudent->current_count << endl;
//     load_weightages(); 
//     for (int i = 0; i < currentStudent->current_count; i++) {
//         course* currentCourse = &currentStudent->courses[i];
        
//         for ( int j = 0 ; j < 3 ; j++ ) {
//             if ( weightage[j].courseType == currentCourse->courseType ) {
//                 currentCourse->qWeight = weightage[j].quizW;
//                 currentCourse->eWeight = weightage[j].examW;
//                 currentCourse->aWeight = weightage[j].assignW;
//             }
//         } 

//        string folderPath = "../data/"; 
// string fileName = folderPath + trim(currentCourse->Coursename) + ".txt"; 
// cout << fileName << endl;
// ifstream recordFile(fileName);
//         if (!recordFile.is_open()) {
//             cout << "error opening record file " << endl ;  
//         continue ;        }
//         else {
//             cout << "opening record file " << endl ;         }

//         string line;

//         // --- STEP C: SEARCH FOR THE STUDENT ID ---
//        while (getline(recordFile, line)  )  {
//     if (line.empty()) continue;
//     cout << "Reading line : " << line << endl ; 

//     stringstream ss(line);
//     string idStr, nameStr;

//     // 1. Read the ID (e.g., s1002)
//     getline(ss, idStr, '|');
//     idStr = trim(idStr);

//     getline(ss, nameStr, '|');

//     cout << "ID" << idStr << endl ; 
//     if (idStr == "s" + to_string(student_id)) {
//         cout << "Found student record for ID: " << idStr << endl;
//         double max_vals[6] = {10, 10, 50, 50, 20, 20};
//         double weights[6] = {
//             currentCourse->qWeight/2, currentCourse->qWeight/2, 
//             currentCourse->eWeight/2, currentCourse->eWeight/2, 
//             currentCourse->aWeight/2, currentCourse->aWeight/2
//         };
//         for ( int i = 0 ; i < 6 ; i++ ) {
//             cout << "Weights " << endl ;
//             cout << weights[i] << endl ; 
//         }

//         // 4. Read the 6 scores
//         for (int k = 0; k < 6; k++) {
//             string scoreStr;
//             if (getline(ss, scoreStr, '|')) {
//                 string cleanScore = trim(scoreStr);
                
//                 if (!cleanScore.empty()) {
//                     try {
//                         double raw = stod(cleanScore);
//                         currentCourse->assessments[k]->set_data(raw, max_vals[k], weights[k]);
//                     } catch (...) {
//                         cout << "Warning: Invalid score [" << cleanScore << "] for student " << idStr << endl;
//                     }
//                 }
//             }
//         }
//         break; 
//     }
//     else {
//         cout << "Student not found in record " << fileName << endl ; 
//     }
// }
//         recordFile.close() ; }
// }
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
        delete students[i]; 
    }
    delete[] students;
    delete[] courses;
    for (int i = 0; i < teacherCount; i++) {
        delete teachers[i]; 
    }
    delete[] teachers ; 
}
