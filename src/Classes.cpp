#include <iostream>
#include "Classes.h"

Classes :: Classes ( string courseID  , string courseName  , int student_count  , string type  , bool isAssigned ){
    this->courseID = courseID ;
    this->courseName = courseName ; 
    this->student_count = student_count ; 
    this->isAssigned = isAssigned ; 
}