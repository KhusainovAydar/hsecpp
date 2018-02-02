кон#include <iostream>
#include <cmath>

class Complex {
  private:
    double x, y;

  public:
    Complex()
        : x(0)
        , y(0) {}
    Complex(double newX, double newY)
        : x(newX)
        , y(newY) {}

    Complex(double newX)
        : x(newX)
        , y(0) {}
    double Re() const {
        return x;
    }

    double Im() const {
        return y;
    }

    Complex& operator += (const Complex& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Complex& operator -= (const Complex& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Complex& operator *= (const Complex& other) {
        auto copyX = x * other.x - y * other.y;
        y = y * other.x + x * other.y;
        x = copyX;
        return *this;
    }

    Complex& operator /= (const Complex& other) {
        auto CopyX = (x * other.x + y * other.y) / (other.x * other.x + other.y * other.y);
        y = (y * other.x - x * other.y) / (other.x * other.x + other.y * other.y);
        x = CopyX;
        return *this;
    }
    Complex operator - () const {
        auto C = Complex();
        return C -= *this;
    }

    Complex operator + () const {
        auto C = *this;
        return C;
    }
};

bool operator == (const Complex& a, const Complex& b) {
    return a.Re() == b.Re() && a.Im() == b.Im();
}

bool operator != (const Complex& a, const Complex& b) {
    return !(a == b);
}

Complex operator + (const Complex& a, const Complex& b) {
    auto C = a;
    C += b;
    return C;
}

Complex operator - (const Complex& a, const Complex& b) {
    auto C = a;
    C -= b;
    return C;
}

Complex operator * (const Complex& a, const Complex& b) {
    auto C = a;
    C *= b;
    return C;
}

Complex operator / (const Complex& a, const Complex& b) {
    auto C = a;
    C /= b;
    return C;
}

double abs(const Complex& other) {
    return std::hypot(other.Re(), other.Im());
}
