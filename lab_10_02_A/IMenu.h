#pragma once
#include "ISpeciality.h"
#include "IStudent.h"
#include <vector>

namespace Menu {
	void inputData(std::string& surname, unsigned int& course, Speciality& speaciality, int& physics, int& math, int& it);
	void printStudents(const std::vector<Student>& students);
	void printMainMenu();
	void clear();
}
