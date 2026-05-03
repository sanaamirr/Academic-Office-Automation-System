#include <iostream>
#include "../include/AcademicEntity.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include"../include/Assessment.h"
#include <fstream>
using namespace std ; 

Assessment :: Assessment ( double weightage  , double score  , int max_score  ){
    this->weightage = weightage ;
    this->raw_score = score ; 
    this->max_score = max_score ; 
}
void Assessment::set_data(double raw, double max, double w) {
    cout << "Setting data" << endl ; 
    this->raw_score = raw;
    this->max_score = max;
    this->weightage = w;
cout << "Setting Assessment: Marks=" << raw_score << ", Max=" << max_score << ", Weight=" << weightage << endl;
}

Exam :: Exam (  double weightage   , double raw_score , int max_score  ) : Assessment ( weightage , raw_score , max_score ) {} 
double Exam :: calculate () {
    if (max_score <= 0) return 0.0;
    return (raw_score/max_score )* weightage ; 

}

Quiz :: Quiz (  double weightage  , double raw_score  , int max_score ) : Assessment ( weightage , raw_score , max_score ) {
}
double Quiz :: calculate  () {
    if (max_score <= 0) return 0.0;
    return (raw_score/max_score )* weightage ; 
}


Assignment :: Assignment (  double weightage  , double raw_score   , int max_score  ) : Assessment ( weightage , raw_score , max_score ) {
} 
double Assignment :: calculate  () {
    if (max_score <= 0) return 0.0;
    return (raw_score/max_score )* weightage ; 
}
