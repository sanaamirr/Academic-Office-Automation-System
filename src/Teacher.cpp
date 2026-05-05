#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include "../include/AcademicEntity.h"
#include "../include/Teacher.h"
using namespace std ;

Teacher :: Teacher ( string id , string name , string email , string department , string subject ) : AcademicEntity ( id , name , email ) {
this->department = department ;
this->subject = subject ; 
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
// checking if the teacher is teaching this course or not 
// how do i access the teachers info here doing this stuff in the main 
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
cout << "Which record do you want to update ? " << endl ; 
cin >> record_to_update ;
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
    << "Department : " << this->department << endl 
    << "Subject : " << this->subject << endl ;
}