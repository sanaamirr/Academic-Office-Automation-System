#include <iostream>
#ifndef TEACHER_H
#define TEACHER_H
#include "AcademicEntity.h"

class Teacher : public AcademicEntity {
protected :
string department ;
string subject ;
public :
Teacher (string id = "" , string name = "" , string email = "" , string department = "" , string subject = "") ;
void updateRecord ( const string& courseName ) ; 
void display () override ; 
};
#endif 