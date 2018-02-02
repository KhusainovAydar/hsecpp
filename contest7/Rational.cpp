#include <iostream>
#include <algorithm>

class Rational {
  private:
    int num;
    int den;

  public:
    Rational()
        : num(0)
        , den(1) {}

    Rational(const Rational& other)
        : num(other.num)
        , den(other.den) {
        int checkin = 1;
        if (den < 0) {
            checkin *= -1;
        }
        if (num < 0) {
            checkin *= -1;
        }
        num = std::abs(num);
        den = std::abs(den);
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        num *= checkin;
    }

    Rational(int x, int y)
        : num(x)
        , den(y) {
        *this = Rational(*this);
    }

    Rational(int x)
        : num(x)
        , den(1) {}

    int numerator() const {
        return num;
    }

    int denominator() const {
        return den;
    }

    Rational& operator += (Rational other) {
        num *= other.den;
        num += other.num * den;
        den *= other.den;
        *this = Rational(*this);
        return *this;
    }

    Rational& operator -= (Rational other) {
        num *= other.den;
        num -= other.num * den;
        den *= other.den;
        *this = Rational(*this);
        return *this;
    }

    Rational& operator *= (Rational other) {
        num *= other.num;
        den *= other.den;
        *this = Rational(*this);
        return *this;
    }

    Rational& operator /= (Rational other) {
        num *= other.den;
        den *= other.num;
        *this = Rational(*this);
        return *this;
    }

    Rational operator + () const {
        auto C = *this;
        return C;
    }

    Rational operator - () const {
        auto C = Rational();
        C -= *this;
        C = Rational(C);
        return C;
    }

    Rational& operator++ () {
        num += den;
        *this = Rational(*this);
        return *this;
    }

    Rational& operator-- () {
        num -= den;
        *this = Rational(*this);
        return *this;
    }

    Rational operator++ (int) {
        Rational temp(*this);
        num += den;
        temp = Rational(temp);
        return temp;
    }

    Rational operator-- (int) {
        Rational temp(*this);
        num -= den;
        temp = Rational(temp);
        return temp;
    }
};

bool operator == (const Rational& a, const Rational& b) {
    return a.numerator() * b.denominator() == a.denominator() * b.numerator();
}

bool operator != (const Rational& a, const Rational& b) {
    return !(a == b);
}

Rational operator + (const Rational& a, const Rational& b) {
    auto C = a;
    C += b;
    return C;
}

Rational operator - (const Rational& a, const Rational& b) {
    auto C = a;
    C -= b;
    return C;
}

Rational operator * (const Rational& a, const Rational& b) {
    auto C = a;
    C *= b;
    return C;
}

Rational operator / (const Rational& a, const Rational& b) {
    auto C = a;
    C /= b;
    return C;
}
