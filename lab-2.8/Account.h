#pragma once
#include <string>
#include <iostream>

class Account {
public:
    class Date {
    private:
        unsigned int year;
        unsigned int month;
        unsigned int day;
        static int counter;

        bool isValidDate(unsigned int y, unsigned int m, unsigned int d) const;
        unsigned int daysInMonth(unsigned int y, unsigned int m) const;

    public:
        unsigned int getYear() const { return year; }
        unsigned int getMonth() const { return month; }
        unsigned int getDay() const { return day; }

        bool setYear(unsigned int y);
        bool setMonth(unsigned int m);
        bool setDay(unsigned int d);

        Date();
        Date(unsigned int y, unsigned int m, unsigned int d);
        Date(const std::string& dateStr);
        Date(const Date& other);
        ~Date();

        Date addDays(int d) const;
        Date subtractDays(int d) const;
        bool isLeapYear() const;
        int compare(const Date& other) const;
        int daysBetween(const Date& other) const;

        Date& operator=(const Date& other);
        operator std::string() const;
        Date& operator++();
        Date& operator--();
        Date operator++(int);
        Date operator--(int);

        friend std::ostream& operator<<(std::ostream& out, const Date& d);
        friend std::istream& operator>>(std::istream& in, Date& d);

        static int getCounter();
    };

private:
    std::string surname;
    int accNumber;
    Date openDate;
    double interestRate;
    double balance;
    static int counter;

    std::string numberToWords(int num) const;

public:
    std::string getSurname() const { return surname; }
    int getAccNumber() const { return accNumber; }
    Date getOpenDate() const { return openDate; }
    double getInterestRate() const { return interestRate; }
    double getBalance() const { return balance; }

    bool setSurname(const std::string& s);
    bool setAccNumber(int num);
    bool setOpenDate(const Date& d);
    bool setInterestRate(double rate);
    bool setBalance(double bal);

    Account();
    Account(std::string s, int accNum, const Date& d, double rate, double bal);
    Account(const Account& other);
    ~Account();

    void changeOwner(const std::string& newOwner);
    bool withdraw(double amount);
    void deposit(double amount);
    void accrueInterest();
    double toUSD(double exchangeRate) const;
    double toEUR(double exchangeRate) const;
    std::string sumToWords() const;
    void updateInterestRate(const Date& currentDate);

    Account& operator=(const Account& other);
    operator std::string() const;
    Account& operator++();
    Account& operator--();
    Account operator++(int);
    Account operator--(int);

    friend std::ostream& operator<<(std::ostream& out, const Account& acc);
    friend std::istream& operator>>(std::istream& in, Account& acc);

    static int getCounter();
};