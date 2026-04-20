#ifndef ACADEMICENTITY_H
#define ACADEMICENTITY_H

#include <iostream>
#include <string>
using namespace std ; 

class AcademicEntity {
protected :
string ID ;
string name ;
string email ; 
public :
// making a parametrized constructor to initialize data members 
AcademicEntity( string ID , string name , string email ) {
    this->ID = ID ;
    this->name = name ; 
    this->email = email ; 
}
virtual void display () = 0 ; 
virtual ~AcademicEntity () {}
};

#endif
