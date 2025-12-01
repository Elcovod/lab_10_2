#include "IStudentManager.h"
#include "ISpeciality.h"
#include <utility>
#include <iostream>
#include <algorithm>

namespace StudentManager {
    unsigned int serial_number = 1;

    Student CreateStudent(const std::string& surname, unsigned int course, Speciality speciality,
        int physics, int math, int it) {
        Student new_student;
        new_student.serial_number = serial_number++;
        new_student.surname = surname;
        new_student.course = course;
        new_student.speciality = speciality;
        new_student.physics = physics;
        new_student.math = math;
        new_student.it = it;
        return new_student;
    }

    // 1. Фізичне сортування
    void physicalSort(std::vector<Student>& students) {
        size_t n = students.size();
        for (size_t i = 0; i < n; i++) {
            size_t best_index = i;
            for (size_t j = i + 1; j < n; j++) {
                // 1 черга: Спеціальність
                if (students[j].speciality < students[best_index].speciality) {
                    best_index = j;
                }
                else if (students[j].speciality == students[best_index].speciality) {
                    // 2 черга: Оцінка з третього предмету
                    if (students[j].it < students[best_index].it) {
                        best_index = j;
                    }
                    else if (students[j].it == students[best_index].it) {
                        // 3 черга: Прізвище
                        if (students[j].surname < students[best_index].surname) {
                            best_index = j;
                        }
                    }
                }
            }
            std::swap(students[i], students[best_index]);
        }
    }

    // 2. Індексне сортування
    std::vector<int> indexSort(const std::vector<Student>& students) {
        std::vector<int> indexes;
        size_t n = students.size();
        for (size_t i = 0; i < n; i++) indexes.push_back(i);

        for (size_t i = 0; i < n; i++) {
            size_t best_index = i;
            for (size_t j = i + 1; j < n; j++) {
                // Використовуємо індекси для доступу до студентів
                if (students[indexes[j]].speciality < students[indexes[best_index]].speciality) {
                    best_index = j;
                }
                else if (students[indexes[j]].speciality == students[indexes[best_index]].speciality) {
                    if (students[indexes[j]].it < students[indexes[best_index]].it) {
                        best_index = j;
                    }
                    else if (students[indexes[j]].it == students[indexes[best_index]].it) {
                        if (students[indexes[j]].surname < students[indexes[best_index]].surname) {
                            best_index = j;
                        }
                    }
                }
            }
            std::swap(indexes[i], indexes[best_index]);
        }
        return indexes;
    }

    // 3. Бінарний пошук
    Student binarySearch(const std::vector<Student>& students, Speciality target_spec,
        int target_grade, std::string target_name) {

        int left = 0;
        int right = students.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // Порівнюємо спочатку за Спеціальністю
            if (students[mid].speciality == target_spec) {
                // Якщо спец. збігається, порівнюємо за Оцінкою
                if (students[mid].it == target_grade) {
                    // Якщо оцінка збігається, порівнюємо за Прізвищем
                    if (students[mid].surname == target_name) {
                        return students[mid]; // Знайшли!
                    }
                    else if (students[mid].surname < target_name) {
                        left = mid + 1;
                    }
                    else {
                        right = mid - 1;
                    }
                }
                else if (students[mid].it < target_grade) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
            else if (students[mid].speciality < target_spec) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        throw std::runtime_error("Студента не знайдено.");
    }

    void toString(const Student& student) {
        std::cout << "Student: {\n\t"
            << "last_name: " << student.surname << ", \n\t"
            << "course: " << student.course << ", \n\t"
            << "speciality: " << ::specialities[(int)student.speciality] << ", \n\t"
            << "physics_grade: " << student.physics << ", \n\t"
            << "math_grade: " << student.math << ", \n\t"
            << "third_grade: " << student.it << "\n"
            << "};" << std::endl;
    }
}