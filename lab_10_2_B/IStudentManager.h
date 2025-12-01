#pragma once
#include <vector>
#include <string>
#include "IStudent.h"

namespace StudentManager {
    extern unsigned int serial_number;

    Student CreateStudent(const std::string& surname, unsigned int course, Speciality speciality,
        int physics, int math, int third_grade);

    void physicalSort(std::vector<Student>& students);
    std::vector<int> indexSort(const std::vector<Student>& students);

    Student binarySearch(const std::vector<Student>& students, Speciality speciality,
        int third_grade, std::string surname);

    void toString(const Student& student);

    int getThirdGrade(const Student& s);
}