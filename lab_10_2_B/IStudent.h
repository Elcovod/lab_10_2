#pragma once
#include <string>
#include "ISpeciality.h"

struct Student
{
    unsigned int serial_number;
    std::string surname;
    unsigned int course;
    Speciality speciality;
    int physics;
    int math;

    union {
        int programming;      
        int num_methods;      
        int pedagogy;       
    };
};