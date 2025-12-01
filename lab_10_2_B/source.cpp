#include <iostream>
#include <Windows.h>
#include <vector>
#include "IMenu.h"
#include "IStudentManager.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::vector<Student> student_list;

    while (true) {
        Menu::printMainMenu();
        short choice;
        std::cout << "Оберіть дію: "; std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string surname;
            Speciality speciality;
            unsigned int course;
            int physics, math, third_grade;

            Menu::clear();
            int cnt;
            std::cout << "Кількість студентів: "; std::cin >> cnt;

            Menu::clear();
            for (int i = 0; i < cnt; i++) {
                Menu::inputData(surname, course, speciality, physics, math, third_grade);
                // CreateStudent сам розбереться, в яке поле Union запхати third_grade
                student_list.push_back(StudentManager::CreateStudent(surname, course, speciality, physics, math, third_grade));
            }
            break;
        }
        case 2:
            if (!student_list.empty()) {
                StudentManager::physicalSort(student_list);
                Menu::clear();
                std::cout << "Відсортовано фізично.\n";
            }
            break;
        case 3:
            if (!student_list.empty()) {
                auto indexes = StudentManager::indexSort(student_list);
                Menu::clear();
                std::cout << "Індексний масив: ";
                for (int i : indexes) std::cout << i << " ";
                std::cout << "\n";
            }
            break;
        case 4: {
            if (student_list.empty()) {
                Menu::clear(); std::cout << "Список порожній.\n"; break;
            }
            // Для бінарного пошуку потрібен відсортований масив
            StudentManager::physicalSort(student_list);

            std::string target_surname;
            int spec_int, target_grade;

            std::cout << "--- Пошук ---\n";
            std::cout << "Спеціальність (0-4): "; std::cin >> spec_int;
            std::cout << "Оцінка з профільного предмету: "; std::cin >> target_grade;
            std::cout << "Прізвище: "; std::cin >> target_surname;

            try {
                Student found = StudentManager::binarySearch(student_list, (Speciality)spec_int, target_grade, target_surname);
                Menu::clear();
                std::cout << "Знайдено:\n";
                StudentManager::toString(found);
            }
            catch (const std::exception& e) {
                Menu::clear();
                std::cout << e.what() << "\n";
            }
            break;
        }
        case 5:
            Menu::clear();
            Menu::printStudents(student_list);
            break;
        case 0:
            return 0;
        default:
            Menu::clear();
            std::cout << "Невірна дія.\n";
        }
    }
}