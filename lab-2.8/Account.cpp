#include "Account.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Ініціалізація статичних полів
int Account::counter = 0;
int Account::Date::counter = 0;

// ================= Реалізація класу Date =================

bool Account::Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned int Account::Date::daysInMonth(unsigned int y, unsigned int m) const {
    if (m == 2) {
        bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        return leap ? 29 : 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

bool Account::Date::isValidDate(unsigned int y, unsigned int m, unsigned int d) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    return d <= daysInMonth(y, m);
}

bool Account::Date::setYear(unsigned int y) {
    if (isValidDate(y, month, day)) { year = y; return true; }
    return false;
}

bool Account::Date::setMonth(unsigned int m) {
    if (isValidDate(year, m, day)) { month = m; return true; }
    return false;
}

bool Account::Date::setDay(unsigned int d) {
    if (isValidDate(year, month, d)) { day = d; return true; }
    return false;
}

Account::Date::Date() : year(2000), month(1), day(1) {
    counter++;
}

Account::Date::Date(unsigned int y, unsigned int m, unsigned int d) {
    if (isValidDate(y, m, d)) { year = y; month = m; day = d; }
    else { year = 2000; month = 1; day = 1; }
    counter++;
}

Account::Date::Date(const string& dateStr) {
    unsigned int y, m, d; char dot1, dot2;
    stringstream ss(dateStr);
    if (ss >> y >> dot1 >> m >> dot2 >> d && dot1 == '.' && dot2 == '.' && isValidDate(y, m, d)) {
        year = y; month = m; day = d;
    }
    else {
        year = 2000; month = 1; day = 1;
    }
    counter++;
}

Account::Date::Date(const Date& other) {
    year = other.year; month = other.month; day = other.day;
    counter++;
}

Account::Date::~Date() {
    counter--;
}

Account::Date Account::Date::addDays(int d) const {
    Date res = *this;
    while (d > 0) {
        unsigned int dim = res.daysInMonth(res.year, res.month);
        if (res.day + d <= dim) { res.day += d; d = 0; }
        else {
            d -= (dim - res.day + 1); res.day = 1; res.month++;
            if (res.month > 12) { res.month = 1; res.year++; }
        }
    }
    return res;
}

Account::Date Account::Date::subtractDays(int d) const {
    Date res = *this;
    while (d > 0) {
        if (res.day > (unsigned int)d) { res.day -= d; d = 0; }
        else {
            d -= res.day;
            if (res.month == 1) { res.month = 12; res.year--; }
            else { res.month--; }
            res.day = res.daysInMonth(res.year, res.month);
        }
    }
    return res;
}

int Account::Date::compare(const Date& other) const {
    if (year != other.year) return (year < other.year) ? -1 : 1;
    if (month != other.month) return (month < other.month) ? -1 : 1;
    if (day != other.day) return (day < other.day) ? -1 : 1;
    return 0;
}

int Account::Date::daysBetween(const Date& other) const {
    Date d1 = *this, d2 = other;
    if (d1.compare(d2) > 0) swap(d1, d2);
    int count = 0;
    while (d1.compare(d2) < 0) { d1 = d1.addDays(1); count++; }
    return count;
}

Account::Date& Account::Date::operator=(const Date& other) {
    if (this != &other) {
        year = other.year; month = other.month; day = other.day;
    }
    return *this;
}

Account::Date::operator string() const {
    stringstream ss;
    ss << setfill('0') << setw(4) << year << "." << setw(2) << month << "." << setw(2) << day;
    return ss.str();
}

Account::Date& Account::Date::operator++() {
    *this = addDays(1);
    return *this;
}

Account::Date& Account::Date::operator--() {
    *this = subtractDays(1);
    return *this;
}

Account::Date Account::Date::operator++(int) {
    Date tmp = *this;
    *this = addDays(1);
    return tmp;
}

Account::Date Account::Date::operator--(int) {
    Date tmp = *this;
    *this = subtractDays(1);
    return tmp;
}

ostream& operator<<(ostream& out, const Account::Date& d) {
    out << string(d);
    return out;
}

istream& operator>>(istream& in, Account::Date& d) {
    unsigned int y, m, day;
    cout << "Введіть рік, місяць та день (через пробіл): ";
    in >> y >> m >> day;
    if (d.isValidDate(y, m, day)) {
        d.year = y; d.month = m; d.day = day;
    }
    return in;
}

int Account::Date::getCounter() {
    return counter;
}


// ================= Реалізація класу Account =================

bool Account::setSurname(const string& s) {
    if (!s.empty()) { surname = s; return true; } return false;
}
bool Account::setAccNumber(int num) {
    if (num > 0) { accNumber = num; return true; } return false;
}
bool Account::setOpenDate(const Date& d) {
    openDate = d; return true;
}
bool Account::setInterestRate(double rate) {
    if (rate >= 0.0) { interestRate = rate; return true; } return false;
}
bool Account::setBalance(double bal) {
    if (bal >= 0.0) { balance = bal; return true; } return false;
}

Account::Account() : surname("Unknown"), accNumber(1), openDate(), interestRate(0.0), balance(0.0) {
    counter++;
}

Account::Account(string s, int accNum, const Date& d, double rate, double bal) : openDate(d) {
    if (!setSurname(s)) surname = "Unknown";
    if (!setAccNumber(accNum)) accNumber = 1;
    if (!setInterestRate(rate)) interestRate = 0.0;
    if (!setBalance(bal)) balance = 0.0;
    counter++;
}

Account::Account(const Account& other) : openDate(other.openDate) {
    surname = other.surname;
    accNumber = other.accNumber;
    interestRate = other.interestRate;
    balance = other.balance;
    counter++;
}

Account::~Account() {
    counter--;
}

void Account::changeOwner(const string& newOwner) { setSurname(newOwner); }

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) { balance -= amount; return true; }
    return false;
}

void Account::deposit(double amount) { if (amount > 0) balance += amount; }
void Account::accrueInterest() { balance += balance * (interestRate / 100.0); }
double Account::toUSD(double exchangeRate) const { return balance / exchangeRate; }
double Account::toEUR(double exchangeRate) const { return balance / exchangeRate; }

void Account::updateInterestRate(const Date& currentDate) {
    if (currentDate.compare(openDate) >= 0) {
        int daysPassed = currentDate.daysBetween(openDate);
        interestRate += daysPassed * 0.01;
    }
}

string Account::numberToWords(int num) const {
    if (num == 0) return "нуль ";
    string ones[] = { "", "одна", "дві", "три", "чотири", "п'ять", "шість", "сім", "вісім", "дев'ять" };
    string teens[] = { "десять", "одинадцять", "дванадцять", "тринадцять", "чотирнадцять", "п'ятнадцять", "шістнадцять", "сімнадцять", "вісімнадцять", "дев'ятнадцять" };
    string tens[] = { "", "", "двадцять", "тридцять", "сорок", "п'ятдесят", "шістдесят", "сімдесят", "вісімдесят", "дев'яносто" };
    string hundreds[] = { "", "сто", "двісті", "триста", "чотириста", "п'ятсот", "шістсот", "сімсот", "вісімсот", "дев'ятсот" };

    string res = "";
    int t = num / 1000;
    if (t > 0) {
        if (t / 100 > 0) res += hundreds[t / 100] + " ";
        int remT = t % 100;
        if (remT >= 10 && remT < 20) res += teens[remT - 10] + " тисяч ";
        else {
            if (remT / 10 > 0) res += tens[remT / 10] + " ";
            if (remT % 10 == 1) res += "одна тисяча ";
            else if (remT % 10 == 2) res += "дві тисячі ";
            else if (remT % 10 >= 3 && remT % 10 <= 4) res += ones[remT % 10] + " тисячі ";
            else if (remT % 10 != 0) res += ones[remT % 10] + " тисяч ";
            else res += "тисяч ";
        }
    }

    int u = num % 1000;
    if (u / 100 > 0) res += hundreds[u / 100] + " ";
    int remU = u % 100;
    if (remU >= 10 && remU < 20) res += teens[remU - 10] + " ";
    else {
        if (remU / 10 > 0) res += tens[remU / 10] + " ";
        if (remU % 10 > 0) res += ones[remU % 10] + " ";
    }
    return res;
}

string Account::sumToWords() const {
    int uah = (int)floor(balance);
    int kop = (int)round((balance - uah) * 100);
    stringstream ss;
    ss << numberToWords(uah) << "грн. " << kop << " коп.";
    return ss.str();
}

Account& Account::operator=(const Account& other) {
    if (this != &other) {
        surname = other.surname;
        accNumber = other.accNumber;
        openDate = other.openDate;
        interestRate = other.interestRate;
        balance = other.balance;
    }
    return *this;
}

Account::operator string() const {
    stringstream ss;
    ss << "Рахунок №" << accNumber << " | Власник: " << surname
        << " | Відкрито: " << string(openDate)
        << " | Ставка: " << interestRate << "% | Баланс: " << fixed << setprecision(2) << balance << " грн.";
    return ss.str();
}

// Інкремент/декремент змінюють баланс на 100
Account& Account::operator++() {
    balance += 100.0;
    return *this;
}

Account& Account::operator--() {
    balance -= 100.0;
    if (balance < 0) balance = 0;
    return *this;
}

Account Account::operator++(int) {
    Account tmp = *this;
    balance += 100.0;
    return tmp;
}

Account Account::operator--(int) {
    Account tmp = *this;
    balance -= 100.0;
    if (balance < 0) balance = 0;
    return tmp;
}

ostream& operator<<(ostream& out, const Account& acc) {
    out << string(acc);
    return out;
}

istream& operator>>(istream& in, Account& acc) {
    cout << "Введіть прізвище: "; in >> acc.surname;
    cout << "Введіть номер рахунку: "; in >> acc.accNumber;
    cout << "Введіть дату відкриття:\n"; in >> acc.openDate;
    cout << "Введіть відсоток нарахування: "; in >> acc.interestRate;
    cout << "Введіть суму на рахунку: "; in >> acc.balance;
    return in;
}

int Account::getCounter() {
    return counter;
}