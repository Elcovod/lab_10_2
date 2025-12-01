#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <algorithm>

#include "F:\Project\lab_10_2_B\Speciality.cpp"
#include "F:\Project\lab_10_2_B\StudentManager.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace LB102BUnitTest
{
	TEST_CLASS(LB102BUnitTest)
	{
	public:

		TEST_METHOD(TestPhysicalSort_WithUnion)
		{
			vector<Student> students;

			students.push_back(StudentManager::CreateStudent("Z_Info", 1, Speciality::INFORMATICS, 5, 5, 80));
			students.push_back(StudentManager::CreateStudent("A_CS_90", 1, Speciality::COMPUTER_SCIENCE, 5, 5, 90));
			students.push_back(StudentManager::CreateStudent("B_CS_100", 1, Speciality::COMPUTER_SCIENCE, 5, 5, 100));

			StudentManager::physicalSort(students);

			Assert::AreEqual(string("A_CS_90"), students[0].surname);
			Assert::AreEqual(string("B_CS_100"), students[1].surname);
			Assert::AreEqual(string("Z_Info"), students[2].surname);
		}

		TEST_METHOD(TestIndexSort)
		{
			vector<Student> students;
			students.push_back(StudentManager::CreateStudent("B", 1, Speciality::INFORMATICS, 5, 5, 50));
			students.push_back(StudentManager::CreateStudent("A", 1, Speciality::COMPUTER_SCIENCE, 5, 5, 50));

			vector<int> indexes = StudentManager::indexSort(students);

			Assert::AreEqual(1, indexes[0]);
			Assert::AreEqual(0, indexes[1]);

			Assert::AreEqual(string("B"), students[0].surname);
		}

		TEST_METHOD(TestBinarySearch_Found)
		{
			vector<Student> students;
			students.push_back(StudentManager::CreateStudent("Petrov", 1, Speciality::COMPUTER_SCIENCE, 5, 5, 95));
			students.push_back(StudentManager::CreateStudent("Ivanov", 1, Speciality::MATH_ECON, 5, 5, 80));

			StudentManager::physicalSort(students);

			Student found = StudentManager::binarySearch(students, Speciality::COMPUTER_SCIENCE, 95, "Petrov");

			Assert::AreEqual(string("Petrov"), found.surname);
			Assert::AreEqual(95, found.programming);
		}

		TEST_METHOD(TestBinarySearch_NotFound)
		{
			vector<Student> students;
			students.push_back(StudentManager::CreateStudent("Ivanov", 1, Speciality::COMPUTER_SCIENCE, 5, 5, 95));
			StudentManager::physicalSort(students);

			try {
				StudentManager::binarySearch(students, Speciality::COMPUTER_SCIENCE, 99, "Ivanov");
				Assert::Fail(L"Expected exception was not thrown");
			}
			catch (const std::exception&) {
			}
		}

		TEST_METHOD(TestUnionIntegrity)
		{
			Student s = StudentManager::CreateStudent("Test", 1, Speciality::COMPUTER_SCIENCE, 5, 5, 100);

			Assert::AreEqual(100, s.programming);
			Assert::AreEqual(100, s.num_methods);
		}
	};
}