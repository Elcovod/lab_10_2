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
            std::string last_name;
            Speciality speciality;
            unsigned int course;
            int physics_grade, math_grade, it_grade;

            Menu::clear();
            int students_count;
            do {
                std::cout << "Введіть кількість студентів: "; std::cin >> students_count;
            } while (students_count < 1);

            Menu::clear();
            for (int i = 0; i < students_count; i++) {
                Menu::inputData(last_name, course, speciality, physics_grade, math_grade, it_grade);
                Student new_student = StudentManager::CreateStudent(
                    last_name, course, speciality, physics_grade, math_grade, it_grade);
                student_list.push_back(new_student);
            }
            break;
        }
        case 2:
            if (student_list.empty()) {
                Menu::clear();
                std::cout << "Список порожній!\n";
            }
            else {
                StudentManager::physicalSort(student_list);
                Menu::clear();
                std::cout << "Масив фізично відсортовано.\n";
            }
            break;
        case 3: {
            if (student_list.empty()) {
                Menu::clear();
                std::cout << "Список порожній!\n";
            }
            else {
                std::vector<int> sorted_indexes = StudentManager::indexSort(student_list);
                Menu::clear();
                std::cout << "Відсортовані індекси: ";
                for (int i : sorted_indexes) std::cout << i << " ";
                std::cout << "\n";

                // Можна вивести студентів за цими індексами для перевірки (опціонально)
                std::cout << "\nПорядок за індексами:\n";
                for (int i : sorted_indexes) {
                    std::cout << student_list[i].surname << " ("
                        << specialities[student_list[i].speciality] << ")\n";
                }
                std::cout << "\n";
            }
            int pause; std::cout << "0. Назад: "; std::cin >> pause;
            Menu::clear();
            break;
        }
        case 4: {
            if (student_list.empty()) {
                Menu::clear();
                std::cout << "Список порожній! Спочатку додайте студентів та відсортуйте (п.2).\n";
            }
            else {
                // ВАЖЛИВО: Для бінарного пошуку масив має бути відсортований!
                // Робимо швидке сортування перед пошуком, щоб гарантувати коректність
                StudentManager::physicalSort(student_list);

                std::string target_name;
                Speciality target_spec;
                int target_grade;
                int spec_buff;

                std::cout << "--- Пошук ---\n";
                std::cout << "Спочатку введіть спеціальність (ключ №1): 0-6: "; std::cin >> spec_buff;
                target_spec = (Speciality)spec_buff;

                std::cout << "Введіть оцінку з 3-го предмету (ключ №2): "; std::cin >> target_grade;

                std::cout << "Введіть прізвище (ключ №3): "; std::cin >> target_name;

                try {
                    Student found = StudentManager::binarySearch(student_list, target_spec, target_grade, target_name);
                    Menu::clear();
                    std::cout << "Студента знайдено!\n";
                    StudentManager::toString(found);
                }
                catch (const std::exception& e) {
                    Menu::clear();
                    std::cout << e.what() << "\n";
                }
            }
            int pause; std::cout << "0. Назад: "; std::cin >> pause;
            Menu::clear();
            break;
        }
        case 5:
            Menu::clear();
            Menu::printStudents(student_list);
            int pause; std::cout << "0. Назад: "; std::cin >> pause;
            Menu::clear();
            break;
        case 0:
            return 0;
        default:
            Menu::clear();
            std::cout << "Невірна дія\n";
        }
    }
}