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
    
    Rational(int x, int y)
        : num(x)
        , den(y) {}

    Rational(int x)
        : num(x)
        , den(1) {}

    int numerator() const {
        return num;
    }

    int denominator() const {
        return den;
    }

    Rational& operator += (const Rational& other) {
        num *= other.den;
        den *= other.den;
        num += other.num * den / other.den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return *this;
    }

    Rational& operator -= (const Rational& other) {
        num *= other.den;
        den *= other.den;
        num -= other.num * den / other.den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return *this;
    }

    Rational& operator *= (const Rational& other) {
        num *= other.num;
        den *= other.den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return *this;
    }

    Rational& operator /= (const Rational& other) {
        num *= other.den;
        den *= other.num;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return *this;
    }

    Rational operator + () const {
        auto C = *this;
        return C;
    }

    Rational operator - () const {
        auto C = Rational();
        C -= *this;
        return C;
    }

    Rational& operator ++ () {
        num += den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return *this;
    }

    Rational& operator -- () {
        num -= den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return *this;
    }
    
    Rational operator ++ (int) {
        Rational temp(*this);
        num += den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
        return temp;
    }

    Rational operator -- (int) {
        Rational temp(*this);
        num -= den;
        auto C = std::__gcd(num, den);
        num /= C;
        den /= C;
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

int main() {

}
