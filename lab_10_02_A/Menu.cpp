#include "IMenu.h"
#include <iostream>
#include <iomanip>

namespace Menu {
    void inputData(std::string& last_name, unsigned int& course, Speciality& speciality,
        int& physics_grade, int& math_grade, int& it_grade) {
        std::cout << "Введіть прізвище: "; std::cin >> last_name;
        do {
            std::cout << "Введіть курс (1-6): "; std::cin >> course;
        } while (course < 1 || course > 6);

        int speciality_choice;
        do {
            std::cout << "Введіть спеціальність (0-6): "; std::cin >> speciality_choice;
        } while (speciality_choice < 0 || speciality_choice > 6);
        speciality = (Speciality)speciality_choice;

        std::cout << "Введіть оцінку з фізики: "; std::cin >> physics_grade;
        std::cout << "Введіть оцінку з математики: "; std::cin >> math_grade;
        std::cout << "Введіть оцінку з 3-го предмету: "; std::cin >> it_grade;
        clear();
    }

    void printStudents(const std::vector<Student>& students) {
        std::cout << "============================================================================================\n";
        std::cout << "| " << std::setw(3) << "№"
            << " | " << std::setw(15) << "Прізвище"
            << " | " << std::setw(35) << "Спеціальність"
            << " | " << std::setw(5) << "Курс"
            << " | " << std::setw(4) << "Мат."
            << " | " << std::setw(4) << "Фіз."
            << " | " << std::setw(4) << "3-й"
            << " |\n";
        std::cout << "============================================================================================\n";
        for (const auto& student : students) {
            std::string spec_name = specialities[(int)student.speciality];
            std::cout << "| " << std::setw(3) << student.serial_number
                << " | " << std::setw(15) << student.surname
                << " | " << std::setw(35) << spec_name
                << " | " << std::setw(5) << student.course
                << " | " << std::setw(4) << student.math
                << " | " << std::setw(4) << student.physics
                << " | " << std::setw(4) << student.it
                << " |\n";
        }
        std::cout << "============================================================================================\n";
    }

    void printMainMenu() {
        std::cout << "=======================================" << std::endl;
        std::cout << "| 1. Додати студента(-ів)             |" << std::endl;
        std::cout << "| 2. Фізично відсортувати студентів   |" << std::endl;
        std::cout << "| 3. Індексно відсортувати студентів  |" << std::endl;
        std::cout << "| 4. Знайти студента (Binary Search)  |" << std::endl;
        std::cout << "| 5. Вивести всіх студентів           |" << std::endl;
        std::cout << "| 0. Вийти                            |" << std::endl;
        std::cout << "=======================================" << std::endl;
    }

    void clear() {
        std::cout << "\033[2J\033[1;1H"; // ANSI escape code for clearing screen
    }
}