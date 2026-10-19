#include "money.h"

Money::Money() : hryvnia(0), kopyiky(0) {}

Money::Money(long h) {
    if (!Init(h, 0)) {
        hryvnia = 0;
        kopyiky = 0;
    }
}

Money::Money(long h, long k) {
    if (!Init(h, k)) {
        hryvnia = 0;
        kopyiky = 0;
    }
}

Money::Money(const Money& m) : hryvnia(m.hryvnia), kopyiky(m.kopyiky) {}

Money::~Money() {}

long long Money::toKopyiky() const {
    return (long long)hryvnia * 100 + kopyiky;
}

bool Money::Init(long h, long k) {
    if (h < 0 || k < 0) return false;
    hryvnia = h + (k / 100);
    kopyiky = (unsigned char)(k % 100);
    return true;
}

std::string Money::toString() const {
    std::string res = std::to_string(hryvnia) + ",";
    if (kopyiky < 10) {
        res += "0";
    }
    res += std::to_string((int)kopyiky);
    return res;
}

Money Money::operator+(const Money& m) const {
    long long sum = toKopyiky() + m.toKopyiky();
    return Money(sum / 100, sum % 100);
}

Money Money::operator-(const Money& m) const {
    long long diff = toKopyiky() - m.toKopyiky();
    if (diff < 0) {
        return Money(0, 0);
    }
    return Money(diff / 100, diff % 100);
}

Money Money::operator*(double factor) const {
    if (factor < 0) return Money(0, 0);
    long long total = (long long)(toKopyiky() * factor);
    return Money(total / 100, total % 100);
}

Money Money::operator/(double factor) const {
    if (factor <= 0) return Money(0, 0);
    long long total = (long long)(toKopyiky() / factor);
    return Money(total / 100, total % 100);
}

bool Money::operator==(const Money& m) const {
    return toKopyiky() == m.toKopyiky();
}

bool Money::operator>(const Money& m) const {
    return toKopyiky() > m.toKopyiky();
}

bool Money::operator<(const Money& m) const {
    return toKopyiky() < m.toKopyiky();
}

std::ostream& operator<<(std::ostream& out, const Money& m) {
    out << m.toString() << " UAH";
    return out;
}

std::istream& operator>>(std::istream& in, Money& m) {
    long h, k;
    std::cout << "Vvedit hryvni: ";
    in >> h;
    std::cout << "Vvedit kopiyky: ";
    in >> k;
    while (h < 0 || k < 0) {
        std::cout << "Pomylka! Vvedit dodatni znachennya:\n";
        std::cout << "Hryvni: "; in >> h;
        std::cout << "Kopiyky: "; in >> k;
    }
    m.Init(h, k);
    return in;
}