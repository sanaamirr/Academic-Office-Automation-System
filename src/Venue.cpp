#include <iostream>
#include "../include/Venue.h"
using namespace std ;

Venue :: Venue ( string roomID , int capacity , bool hasComputers , bool * isBooked ){
    this->roomID = roomID ; 
    this->capacity = capacity ; 
    this->hasComputers = hasComputers ;
    this->isBooked = new bool [3]; 
}
Venue :: ~Venue () {
    delete [] isBooked ; 
}