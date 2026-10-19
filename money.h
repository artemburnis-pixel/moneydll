#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>
#ifdef MONEYDLL_EXPORTS
#define MONEY_API __declspec(dllexport)
#else
#define MONEY_API __declspec(dllimport)
#endif

class MONEY_API Money {
private:
    long hryvnia;
    unsigned char kopyiky;
    long long toKopyiky() const;
public:
    Money();
    Money(long h);
    Money(long h, long k);
    Money(const Money& m);
    ~Money();

    bool Init(long h, long k);
    std::string toString() const;

    Money operator+(const Money& m) const;
    Money operator-(const Money& m) const;
    Money operator*(double factor) const;
    Money operator/(double factor) const;

    bool operator==(const Money& m) const;
    bool operator>(const Money& m) const;
    bool operator<(const Money& m) const;

    friend MONEY_API std::ostream& operator<<(std::ostream& out, const Money& m);
    friend MONEY_API std::istream& operator>>(std::istream& in, Money& m);
};

#endif