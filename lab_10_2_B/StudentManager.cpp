#include "IStudentManager.h"
#include "ISpeciality.h"
#include <utility>
#include <iostream>
#include <algorithm>

namespace StudentManager {
    unsigned int serial_number = 1;

    // Допоміжна функція: повертає правильну оцінку з Union залежно від спеціальності
    int getThirdGrade(const Student& s) {
        switch (s.speciality) {
        case COMPUTER_SCIENCE: return s.programming;
        case INFORMATICS:      return s.num_methods;
        default:               return s.pedagogy;
        }
    }

    Student CreateStudent(const std::string& surname, unsigned int course, Speciality speciality,
        int physics, int math, int third_grade) {
        Student new_student;
        new_student.serial_number = serial_number++;
        new_student.surname = surname;
        new_student.course = course;
        new_student.speciality = speciality;
        new_student.physics = physics;
        new_student.math = math;

        switch (speciality) {
        case COMPUTER_SCIENCE: new_student.programming = third_grade; break;
        case INFORMATICS:      new_student.num_methods = third_grade; break;
        default:               new_student.pedagogy = third_grade;    break;
        }
        return new_student;
    }

    // 1. Фізичне сортування: Спеціальність -> 3-й предмет -> Прізвище
    void physicalSort(std::vector<Student>& students) {
        size_t n = students.size();
        for (size_t i = 0; i < n; i++) {
            size_t best_index = i;
            for (size_t j = i + 1; j < n; j++) {
               
                if (students[j].speciality < students[best_index].speciality) {
                    best_index = j;
                }
                else if (students[j].speciality == students[best_index].speciality) {
                    // 2. Третя оцінка (використовуємо getThirdGrade або прямий доступ, бо спец. однакові)
                    int gradeA = getThirdGrade(students[j]);
                    int gradeB = getThirdGrade(students[best_index]);

                    if (gradeA < gradeB) {
                        best_index = j;
                    }
                    else if (gradeA == gradeB) {
                    
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
                // Порівнюємо students[indexes[j]] та students[indexes[best_index]]
                const Student& s1 = students[indexes[j]];
                const Student& s2 = students[indexes[best_index]];

                if (s1.speciality < s2.speciality) {
                    best_index = j;
                }
                else if (s1.speciality == s2.speciality) {
                    int grade1 = getThirdGrade(s1);
                    int grade2 = getThirdGrade(s2);

                    if (grade1 < grade2) {
                        best_index = j;
                    }
                    else if (grade1 == grade2) {
                        if (s1.surname < s2.surname) {
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
            const Student& s = students[mid];
            int s_grade = getThirdGrade(s);

            // 1. Перевірка спеціальності
            if (s.speciality == target_spec) {
                // 2. Перевірка оцінки
                if (s_grade == target_grade) {
                    // 3. Перевірка прізвища
                    if (s.surname == target_name) {
                        return s; // Знайшли
                    }
                    else if (s.surname < target_name) {
                        left = mid + 1;
                    }
                    else {
                        right = mid - 1;
                    }
                }
                else if (s_grade < target_grade) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
            else if (s.speciality < target_spec) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        throw std::runtime_error("Студента не знайдено.");
    }

    void toString(const Student& student) {
        std::string third_label;
        int third_val;

        switch (student.speciality) {
        case COMPUTER_SCIENCE:
            third_label = "Programming"; third_val = student.programming; break;
        case INFORMATICS:
            third_label = "Num. Methods"; third_val = student.num_methods; break;
        default:
            third_label = "Pedagogy";     third_val = student.pedagogy;    break;
        }

        std::cout << "Student: {\n\t"
            << "Surname: " << student.surname << ", \n\t"
            << "Course: " << student.course << ", \n\t"
            << "Speciality: " << ::specialities[(int)student.speciality] << ", \n\t"
            << "Physics: " << student.physics << ", \n\t"
            << "Math: " << student.math << ", \n\t"
            << third_label << ": " << third_val << "\n"
            << "};" << std::endl;
    }
}