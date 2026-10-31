#include <iostream>
#include <Windows.h>
#include "Account.h"

using namespace std;

#pragma pack(push, 1)
class PackedDate {
    unsigned int year, month, day;
};
class PackedAccount {
    string surname;
    int accNumber;
    PackedDate openDate;
    double interestRate;
    double balance;
};
#pragma pack(pop)

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Обчислення кількості об'єктів ===\n";
    cout << "Account counter: " << Account::getCounter() << endl;
    cout << "Account::Date counter: " << Account::Date::getCounter() << endl;

    Account::Date d1("2023.10.15");
    Account acc1("Шевченко", 10045, d1, 5.0, 15432.50);

    cout << "\nAccount counter: " << Account::getCounter() << endl;
    cout << "Account::Date counter: " << Account::Date::getCounter() << endl;

    {
        Account acc2; // Виклик конструктора за умовчанням
        cout << "\n(Local block) Account counter: " << Account::getCounter() << endl;
        cout << "(Local block) Account::Date counter: " << Account::Date::getCounter() << endl;
    }

    cout << "\nAfter local block Account counter: " << Account::getCounter() << endl;
    cout << "After local block Account::Date counter: " << Account::Date::getCounter() << endl;


    cout << "\n=== Демонстрація перевантажених операцій ===\n";
    cout << acc1 << endl;

    cout << "\nПрефіксний інкремент (++acc1): збільшує баланс на 100\n";
    cout << ++acc1 << endl;

    cout << "\nПостфіксний декремент (acc1--): зменшує баланс на 100\n";
    Account tmp = acc1--;
    cout << "Повернене значення (до декременту): " << tmp << endl;
    cout << "Поточне значення (після декременту): " << acc1 << endl;

    cout << "\nРобота з датою (зміна дати через індекси Date):\n";
    Account::Date d2 = acc1.getOpenDate();
    cout << "Початкова дата: " << d2 << endl;
    d2++;
    cout << "Після d2++: " << d2 << endl;


    cout << "\n=== Демонстрація #pragma pack(1) ===\n";
    cout << "Розмір класу Account (без pack): " << sizeof(Account) << " байт\n";
    cout << "Розмір класу Account (з pack(1)): " << sizeof(PackedAccount) << " байт\n";

    cout << "\n=== Операція вводу/виводу ===\n";
    Account userAcc;
    cin >> userAcc;
    cout << "\nВи ввели:\n" << userAcc << endl;
    cout << "Сума прописом: " << userAcc.sumToWords() << endl;

    return 0;
}