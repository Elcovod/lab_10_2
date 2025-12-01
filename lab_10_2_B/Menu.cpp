#include "IMenu.h"
#include "IStudentManager.h"
#include <iostream>
#include <iomanip>

namespace Menu {
    void inputData(std::string& surname, unsigned int& course, Speciality& speciality,
        int& physics, int& math, int& third_grade) {

        std::cout << "Введіть прізвище: "; std::cin >> surname;
        do {
            std::cout << "Введіть курс (1-6): "; std::cin >> course;
        } while (course < 1 || course > 6);

        int spec_choice;
        std::cout << "Спеціальність (0-КН, 1-Інф, 2-МатЕк, 3-ФізІнф, 4-Труд): ";
        std::cin >> spec_choice;
        speciality = (Speciality)spec_choice;

        std::cout << "Оцінка з фізики: "; std::cin >> physics;
        std::cout << "Оцінка з математики: "; std::cin >> math;

        // Питаємо правильний предмет
        switch (speciality) {
        case COMPUTER_SCIENCE: std::cout << "Оцінка з програмування: "; break;
        case INFORMATICS:      std::cout << "Оцінка з чис. методів: "; break;
        default:               std::cout << "Оцінка з педагогіки: "; break;
        }
        std::cin >> third_grade;

        clear();
    }

    void printStudents(const std::vector<Student>& students) {
        std::cout << "==========================================================================================\n";
        std::cout << "| " << std::setw(3) << "№"
            << " | " << std::setw(15) << "Прізвище"
            << " | " << std::setw(25) << "Спеціальність"
            << " | " << std::setw(4) << "Курс"
            << " | " << std::setw(4) << "Мат."
            << " | " << std::setw(4) << "Фіз."
            << " | " << std::setw(3) << " 3-й предмет " << " |\n";
        std::cout << "==========================================================================================\n";

        for (const auto& s : students) {
            std::string third_text;
            int third_val;

            switch (s.speciality) {
            case COMPUTER_SCIENCE:
                third_text = "Prog: "; third_val = s.programming; break;
            case INFORMATICS:
                third_text = "NM: ";   third_val = s.num_methods; break;
            default:
                third_text = "Ped: ";  third_val = s.pedagogy;    break;
            }

            std::cout << "| " << std::setw(3) << s.serial_number
                << " | " << std::setw(15) << s.surname
                << " | " << std::setw(25) << ::specialities[(int)s.speciality]
                << " | " << std::setw(4) << s.course
                << " | " << std::setw(4) << s.math
                << " | " << std::setw(4) << s.physics
                << " | " << std::setw(10) << third_text << std::setw(3) << third_val << " |\n";
        }
        std::cout << "==========================================================================================\n";
    }

    void printMainMenu() {
        std::cout << "================ MENU (LB 10.2 Var B) ===============" << std::endl;
        std::cout << "| 1. Додати студентів                               |" << std::endl;
        std::cout << "| 2. Фізичне сортування (Спец -> Оцінка -> Прізв.)  |" << std::endl;
        std::cout << "| 3. Індексне сортування                            |" << std::endl;
        std::cout << "| 4. Бінарний пошук                                 |" << std::endl;
        std::cout << "| 5. Вивести всіх                                   |" << std::endl;
        std::cout << "| 0. Вихід                                          |" << std::endl;
        std::cout << "=====================================================" << std::endl;
    }

    void clear() {
        std::cout << "\033[2J\033[1;1H";
    }
}