#include "pch.h"
#include "CppUnitTest.h"
#include "../lab-2.8/Account.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std; 

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestAccountInitialization)
		{
			// Arrange
			Account::Date testDate("2023.10.15");
			string expectedSurname = "Шевченко";
			int expectedAccNumber = 10045;
			double expectedInterestRate = 5.0;
			double expectedBalance = 15432.50;

			// Act
			Account acc(expectedSurname, expectedAccNumber, testDate, expectedInterestRate, expectedBalance);

			// Assert
			Assert::AreEqual(expectedSurname, acc.getSurname());
			Assert::AreEqual(expectedAccNumber, acc.getAccNumber());
			Assert::AreEqual(expectedInterestRate, acc.getInterestRate());
			Assert::AreEqual(expectedBalance, acc.getBalance());
		}
	};
}