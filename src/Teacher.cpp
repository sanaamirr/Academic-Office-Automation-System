#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include "../include/AcademicEntity.h"
#include "../include/Teacher.h"
using namespace std ;

Teacher :: Teacher ( string id , string name , string email , string department , int rating_count , double total_ratingSum  ) : AcademicEntity ( id , name , email ) {
this->department = department ; 
this->rating_count = rating_count ; 
this->total_ratingSum = total_ratingSum ; 
for (int i = 0; i < 2; i++) {
            assignedCourses[i] = "";
        }
} 

void Teacher :: updateRecord ( const string& courseName ) {
    // checkinng if the course exists in the database 
    string filename = "../data/" + courseName + ".txt" ;
    ifstream coursefile( filename );
    if ( !coursefile.is_open () ) {
        cout << "Course is not found in the database " << endl ; 
    }
    else {
        cout << "Course has been found " << endl ; 
    }
    ofstream tempfile ("temp.txt");
cout << "\n--- Pinpoint Record Update ---" << endl;
cout << "Enter student ID " << endl ;
string studentID ;
cin >> studentID ;
string line ;
bool studentFound = false ; 
while ( getline ( coursefile , line ) ) {
    if ( line.find ( studentID ) != string :: npos ){
        cout << "The upper loop is being executed " << endl ; 
        studentFound = true ; 
        break ; 
    }
}
string record_to_update ; 
bool isValid = false ; 
while (!isValid) {
cout << "Which record do you want to update  ?(Enter in the format qn/Qn or an/An or en/En) " << endl ; 
cin >> record_to_update ;
if (record_to_update.length() == 2) {
        char type = tolower(record_to_update[0]); 
        char num = record_to_update[1];           

        
        if ((type == 'q' || type == 'a' || type == 'e') && (num == '1' || num == '2')) {
            isValid = true;
        }
    }

    if (!isValid) {
        cout << "Invalid format! Use a letter (Q, A, E) followed by 1 or 2." << endl;
    }
}
int count = 0 ;
double new_score ;
switch ( record_to_update[0] ) {
    case 'q' : 
    case 'Q' : 
        switch ( record_to_update[1] ) {
            case '1': 
            cout << "Enter the new score " << endl ;
            cin >> new_score ; 
            
            for ( int i = 0 ;  i < line.length () ; i ++ ) {
                if ( line[i] == '|') {
                   count ++ ;          
                }
                if ( count == 2) {
                    int st_index = i+1 ; 
                    bool isReplaced = false ; 
                    for ( int j = st_index ; j < line.length() ; j++){
                        if ( line[j] == '|'){
                            int end_index = j-1 ; 
                            stringstream ss ;
                            ss << fixed << setprecision(1) << new_score ; 
                            string formatted_score = ss.str() ; 
                            line.replace ( st_index , end_index - st_index + 1 ,formatted_score ) ;
                            isReplaced = true ;  
                            break ; 
                        }
                    }
                    if ( isReplaced == true ){
                        break ; 
                    }

                }
            }
            break ; 
            case '2':
            cout << "Enter the new score " << endl ;
            cin >> new_score ; 
            for ( int i = 0 ;  i < line.length () ; i ++ ) {
                if ( line[i] == '|') {
                   count ++ ;          
                }
                if ( count == 3) {
                    int st_index = i+1 ; 
                    bool isReplaced = false ; 
                    for ( int j = st_index ; j < line.length() ; j++){
                        if ( line[j] == '|'){
                            int end_index = j-1 ; 
                            stringstream ss ;
                            ss << fixed << setprecision(1) << new_score ; 
                            string formatted_score = ss.str() ; 
                            line.replace ( st_index , end_index - st_index + 1 ,formatted_score ) ;
                            isReplaced = true ;  
                            break ; 
                        }
                    }
                    if ( isReplaced == true ){
                        break ; 
                    }

                }
            }
        } 
        cout << "marks have been updates " << endl ; 
        break ; 
    case 'e' : 
    case 'E' : 
        cout << "Updating exam record " << endl ; 
         switch ( record_to_update[1] ) {
            case '1': 
            cout << "Enter the new score " << endl ;
            cin >> new_score ; 
            for ( int i = 0 ;  i < line.length () ; i ++ ) {
                if ( line[i] == '|') {
                   count ++ ;          
                }
                if ( count == 4) {
                    int st_index = i+1 ; 
                    bool isReplaced = false ; 
                    for ( int j = st_index ; j < line.length() ; j++){
                        if ( line[j] == '|'){
                            int end_index = j-1 ; 
                            stringstream ss ;
                            ss << fixed << setprecision(1) << new_score ; 
                            string formatted_score = ss.str() ; 
                            line.replace ( st_index , end_index - st_index + 1 ,formatted_score ) ;
                            isReplaced = true ;  
                            break ; 
                        }
                    }
                    if ( isReplaced == true ){
                        break ; 
                    }

                }
            }
            break ; 
             case '2': 
            cout << "Enter the new score " << endl ;
            cin >> new_score ; 
            for ( int i = 0 ;  i < line.length () ; i ++ ) {
                if ( line[i] == '|') {
                   count ++ ;          
                }
                if ( count == 5) {
                    int st_index = i+1 ; 
                    bool isReplaced = false ; 
                    for ( int j = st_index ; j < line.length() ; j++){
                        if ( line[j] == '|'){
                            int end_index = j-1 ; 
                            stringstream ss ;
                            ss << fixed << setprecision(1) << new_score ; 
                            string formatted_score = ss.str() ; 
                            line.replace ( st_index , end_index - st_index + 1 ,formatted_score ) ;
                            isReplaced = true ;  
                            break ; 
                        }
                    }
                    if ( isReplaced == true ){
                        break ; 
                    }

                }
            }
        } 
        break ; 
        cout << "marks have been updated " << endl ; 
        break ; 
    case 'a' : 
    case 'A' : 
        cout << "Updating assignment record " << endl ; 
         switch ( record_to_update[1] ) {
            case '1': 
            cout << "Enter the new score " << endl ;
            cin >> new_score ; 
            for ( int i = 0 ;  i < line.length () ; i ++ ) {
                if ( line[i] == '|') {
                   count ++ ;          
                }
                if ( count == 6) {
                    int st_index = i+1 ; 
                    bool isReplaced = false ; 
                    for ( int j = st_index ; j < line.length() ; j++){
                        if ( line[j] == '|'){
                            int end_index = j-1 ; 
                            stringstream ss ;
                            ss << fixed << setprecision(1) << new_score ; 
                            string formatted_score = ss.str() ; 
                            line.replace ( st_index , end_index - st_index + 1 ,formatted_score ) ;
                            isReplaced = true ;  
                            break ; 
                        }
                    }
                    if ( isReplaced == true ){
                        break ; 
                    }

                }
            }
            break ; 
             case '2': 
            cout << "Enter the new score " << endl ;
            cin >> new_score ; 
            for ( int i = 0 ;  i < line.length () ; i ++ ) {
                if ( line[i] == '|') {
                   count ++ ;          
                }
                if ( count == 7) {
                    int st_index = i+1 ; 
                    bool isReplaced = false ; 
                    for ( int j = st_index ; j < line.length() ; j++){
                        if ( line[j] == '|'){
                            int end_index = j-1 ; 
                            stringstream ss ;
                            ss << fixed << setprecision(1) << new_score ; 
                            string formatted_score = ss.str() ; 
                            line.replace ( st_index , end_index - st_index + 1 ,formatted_score ) ;
                            isReplaced = true ;  
                            break ; 
                        }
                    }
                    if ( isReplaced == true ){
                        break ; 
                    }

                }
            }
        } 
        cout << "marks have been updates " << endl ; 
        break ; 
    default :
        cout << "Invalid record type " << endl ; 
        break ; 
}
string current_line ; 
cout << "The line outside the loop is " << line << endl ; 
coursefile.clear();                 
coursefile.seekg(0, ios::beg);      
while ( getline(coursefile , current_line)){ 
    if ( current_line.find ( studentID ) != string :: npos){
        tempfile << line << endl ; 
    }
    else {
        tempfile << current_line << endl ; 
    }
}

coursefile.close() ; 
tempfile.close() ; 
 
remove(filename.c_str());
cout << "file operations are being executed "<< endl ; 
rename("temp.txt", filename.c_str());
}

void Teacher :: display () {
    cout << "Teacher ID : " << this->ID << endl  
    << "Teacher Name  : " << this->name << endl <<"Teacher email : " << this->email << endl 
    << "Department : " << this->department << endl; 
}
// void Teacher :: assignCourse(string courseName) {
//         if (courseCount < 10) {
//             assignedCourses[courseCount] = courseName;
//             courseCount++;
//         } else {
//             cout << "Full capacity for Professor " << name << endl;
//         }
//     }
void Teacher :: add_rating( double score  , string teacher_id ){
    if (score< 1 || score > 5) {
        cout << "Error: Rating must be between 1 and 5." << endl;
        return;
    }  
    ifstream file("../data/Teacher.txt");
    ofstream temp("../data/temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(teacher_id) != string::npos) {
            found = true;
            stringstream ss(line);
            string id, name, email, dept, subject, ratingCount, rating;

            // 2. Parse the existing data (Assumes: ID | Name | Email | Dept | Sub | Sum | Count)
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, email, '|');
            getline(ss, dept, '|');
            getline(ss, subject, '|');
            getline(ss, ratingCount, '|');
            getline(ss, rating, '|');

            // 3. Apply the Formula
            // assuming that we will load a teachers array also 
            this->rating_count ++ ; 
             if ( this->rating_count  == 1  ){
                   this->total_ratingSum = score ;
             }
             else {
                this->total_ratingSum = this->total_ratingSum + ( score - this->total_ratingSum) / this->rating_count;
             }
         

            // 4. Reconstruct the line with updated stats
            // We use fixed/setprecision to keep the file looking clean
            stringstream updated;
            updated << id << "|" << name << "|" << email << "|" << dept << "|" << subject << "|" 
                    << fixed << setprecision(1) << ratingCount << "|" << rating  << "|";
            
            temp << updated.str() << endl;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("../data/Teacher.txt");
    rename("../data/temp.txt", "../data/Teacher.txt");

    if (found) cout << "Rating submitted! New Average: " << endl;
    else cout << "Teacher ID not found." << endl;
}

void Teacher :: assignCourse(string courseName) {
        if (courseCount < 10) {
            assignedCourses[courseCount++] = courseName;
        } else {
            cout << "Warning: Teacher course limit reached!" << endl;
        }
    }