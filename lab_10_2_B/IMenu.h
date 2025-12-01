#pragma once
#include "ISpeciality.h"
#include "IStudent.h"
#include <vector>

namespace Menu {
    void inputData(std::string& surname, unsigned int& course, Speciality& speciality,
        int& physics, int& math, int& third_grade);
    void printStudents(const std::vector<Student>& students);
    void printMainMenu();
    void clear();
}
