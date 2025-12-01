#pragma once
#include <vector>
#include <string>
#include "IStudent.h"

namespace StudentManager {
	extern unsigned int serial_number;

	Student CreateStudent(const std::string& surname, unsigned int course, Speciality speciality, int physics, int math, int it);
	void physicalSort(std::vector<Student>& students); //сортування вектора
	std::vector<int> indexSort(const std::vector<Student>& students); //індексне сортування
	Student binarySearch(const std::vector<Student>& students, Speciality speciality, int third_grade, std::string surname); //бінарний пошук
	void toString(const Student& student);
}
