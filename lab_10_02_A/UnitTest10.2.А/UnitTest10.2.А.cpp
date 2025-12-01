#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <algorithm>

#include "F:\Project\lab_10_02_A\Speciality.cpp"
#include "F:\Project\lab_10_02_A\StudentManager.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace LB102AUnitTest
{
	TEST_CLASS(LB102AUnitTest)
	{
	public:

		TEST_METHOD(TestPhysicalSort)
		{
			vector<Student> students;

			students.push_back(StudentManager::CreateStudent("Z_Last", 1, Speciality::F2, 5, 5, 100));
			students.push_back(StudentManager::CreateStudent("A_First", 1, Speciality::F1, 5, 5, 90));
			students.push_back(StudentManager::CreateStudent("B_Second", 1, Speciality::F1, 5, 5, 100));

			StudentManager::physicalSort(students);

			Assert::AreEqual(string("A_First"), students[0].surname);
			Assert::AreEqual(string("B_Second"), students[1].surname);
			Assert::AreEqual(string("Z_Last"), students[2].surname);
		}

		TEST_METHOD(TestIndexSort)
		{
			vector<Student> students;
			students.push_back(StudentManager::CreateStudent("B", 1, Speciality::F2, 5, 5, 50));
			students.push_back(StudentManager::CreateStudent("A", 1, Speciality::F1, 5, 5, 50));

			vector<int> indexes = StudentManager::indexSort(students);

			Assert::AreEqual(1, indexes[0]);
			Assert::AreEqual(0, indexes[1]);

			Assert::AreEqual(string("B"), students[0].surname);
		}

		TEST_METHOD(TestBinarySearch_Found)
		{
			vector<Student> students;
			students.push_back(StudentManager::CreateStudent("Ivanov", 1, Speciality::F1, 5, 5, 95));

			StudentManager::physicalSort(students);

			Student found = StudentManager::binarySearch(students, Speciality::F1, 95, "Ivanov");

			Assert::AreEqual(string("Ivanov"), found.surname);
			Assert::AreEqual(95, found.it);
		}

		TEST_METHOD(TestBinarySearch_NotFound)
		{
			vector<Student> students;
			students.push_back(StudentManager::CreateStudent("Ivanov", 1, Speciality::F1, 5, 5, 95));
			StudentManager::physicalSort(students);

			try {
				StudentManager::binarySearch(students, Speciality::F1, 100, "Ivanov");
				Assert::Fail(L"Expected exception was not thrown");
			}
			catch (const std::exception&) {
			}
		}
	};
}