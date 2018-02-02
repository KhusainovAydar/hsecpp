#include <iostream>
#include <vector>
#include <assert.h>

template<typename T>
class Polynomial {
private:
    std::vector<T> arrPolynomial;
    using ConstIter = typename std::vector<T>::const_iterator;
    using ConstRevIter = typename std::vector<T>::const_reverse_iterator;
    T TypeDefVal;
    void clearZero() {
        while (arrPolynomial.size() && arrPolynomial.back() == TypeDefVal) {
            arrPolynomial.pop_back();
        }
    }
    Polynomial operator << (size_t k) const {
        Polynomial ret;
        ret.arrPolynomial.resize(arrPolynomial.size() + k);
        for (size_t i = 0; i != arrPolynomial.size(); ++i) {
            ret.arrPolynomial[i + k] = arrPolynomial[i];
        }
        return ret;
    }


public:
    Polynomial<T>(const std::vector<T>& arr) {
        arrPolynomial.resize(arr.size());
        for (size_t i = 0; i != arr.size(); ++i) {
            arrPolynomial[i] = arr[i];
        }
        TypeDefVal = T();
        clearZero();
    }

    Polynomial<T>(const T& x = T()) {
        arrPolynomial.clear();
        arrPolynomial.push_back(x);
        TypeDefVal = T();
        clearZero();
    }

    template <typename Iter>
    Polynomial<T>(Iter begin, Iter end) {
        arrPolynomial.clear();
        while (begin != end) {
            arrPolynomial.push_back(*begin);
            ++begin;
        }
        TypeDefVal = T();
        clearZero();
    }

    bool operator == (const Polynomial& other) const {
        return arrPolynomial == other.arrPolynomial;
    }

    bool operator != (const Polynomial& other) const {
        return !(*this == other);
    }

    int Degree() const {
        if (arrPolynomial.empty()) {
            return -1;
        }
        return arrPolynomial.size() - 1;
    }

    const T& operator[] (size_t id) const {
        if (id >= size()) {
            return TypeDefVal;
        }
        return arrPolynomial[id];
    }

    size_t size() const {
        return arrPolynomial.size();
    }


    Polynomial& operator += (const Polynomial& other) {
        for (size_t i = 0; i != other.size(); ++i) {
            if (i == arrPolynomial.size()) {
                arrPolynomial.push_back(other.arrPolynomial[i]);
            } else {
                arrPolynomial[i] += other.arrPolynomial[i];
            }
        }
        clearZero();
        return *this;
    }

    Polynomial& operator -= (const Polynomial& other) {
        for (size_t i = 0; i != other.size(); ++i) {
            if (i == arrPolynomial.size()) {
                arrPolynomial.push_back(other.arrPolynomial[i] * static_cast<T>(-1));
            } else {
                arrPolynomial[i] += other.arrPolynomial[i] * static_cast<T>(-1);
            }
        }
        clearZero();
        return *this;
    }

    Polynomial& operator *= (const Polynomial& other) {
        Polynomial<T> ans;
        ans.arrPolynomial.resize(size() + other.size());
        for (size_t it1 = 0; it1 != size(); ++it1) {
            for (size_t it2 = 0; it2 != other.size(); ++it2) {
                ans.arrPolynomial[it1 + it2] += arrPolynomial[it1] * other.arrPolynomial[it2];
            }
        }
        *this = ans;
        clearZero();
        return *this;
    }

    Polynomial& operator /= (const Polynomial& other) {
        Polynomial<T> quetient, remainder = *this;
        quetient.arrPolynomial.resize(size());
        while (remainder.Degree() >= other.Degree()) {
            T coef = *remainder.rbegin() / *other.rbegin();
            quetient.arrPolynomial[remainder.Degree() - other.Degree()] = coef;
            remainder -= coef * (other << (remainder.Degree() - other.Degree()));
        }
        *this = quetient;
        clearZero();
        return *this;
    }

    Polynomial& operator %= (const Polynomial& other) {
        auto a = *this, b = other;
        a /= b;
        a *= b;
        *this -= a;
        clearZero();
        return *this;
    }

    T operator() (const T& x) const {
        T ans = TypeDefVal;
        T curPow = static_cast<T>(1);
        for (auto it = arrPolynomial.begin();
             it != arrPolynomial.end();
             ++it) {
            ans += *it * curPow;
            curPow *= x;
        }
        return ans;
    }

    ConstIter begin() const {
        return arrPolynomial.begin();
    }

    ConstIter end() const {
        return arrPolynomial.end();
    }

    ConstRevIter rbegin() const {
        return arrPolynomial.rbegin();
    }

    ConstRevIter rend() const {
        return arrPolynomial.rend();
    }
};

template <typename T>
bool operator == (const Polynomial<T>& a, const T& b) {
    return a == Polynomial<T>(b);
}

template <typename T>
bool operator == (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) == b;
}

template <typename T>
bool operator != (const Polynomial<T>& a, const T& b) {
    return a != Polynomial<T>(b);
}

template <typename T>
bool operator != (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) != b;
}

template <typename T>
Polynomial<T> operator + (const Polynomial<T>& a, const Polynomial<T>& b) {
    auto tmp = a;
    tmp += b;
    return tmp;
}

template <typename T>
Polynomial<T> operator + (const Polynomial<T>& a, const T& b) {
    return a + Polynomial<T>(b);
}

template <typename T>
Polynomial<T> operator + (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) + b;
}

template <typename T>
Polynomial<T> operator - (const Polynomial<T>& a, const Polynomial<T>& b) {
    auto tmp = a;
    tmp -= b;
    return tmp;
}

template <typename T>
Polynomial<T> operator - (const Polynomial<T>& a, const T& b) {
    return a - Polynomial<T>(b);
}

template <typename T>
Polynomial<T> operator - (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) - b;
}

template <typename T>
Polynomial<T> operator * (const Polynomial<T>& a, const Polynomial<T>& b) {
    auto tmp = a;
    tmp *= b;
    return tmp;
}

template <typename T>
Polynomial<T> operator * (const Polynomial<T>& a, const T& b) {
    return a * Polynomial<T>(b);
}

template <typename T>
Polynomial<T> operator * (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) * b;
}

template <typename T>
Polynomial<T> operator / (const Polynomial<T>& a, const Polynomial<T>& b) {
    auto tmp = a;
    tmp /= b;
    return tmp;
}

template <typename T>
Polynomial<T> operator / (const Polynomial<T>& a, const T& b) {
    return a / Polynomial<T>(b);
}

template <typename T>
Polynomial<T> operator / (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) / b;
}

template <typename T>
Polynomial<T> operator % (const Polynomial<T>& a, const Polynomial<T>& b) {
    auto tmp = a;
    tmp %= b;
    return tmp;
}

template <typename T>
Polynomial<T> operator % (const Polynomial<T>& a, const T& b) {
    return a % Polynomial<T>(b);
}

template <typename T>
Polynomial<T> operator % (const T& a, const Polynomial<T>& b) {
    return Polynomial<T>(a) % b;
}

template <typename T>
Polynomial<T> operator & (const Polynomial<T>& a, const Polynomial<T>& b) {
    auto ans = Polynomial<T>();
    for (auto it = a.begin(); it != a.end(); it++) {
        auto tmp = Polynomial<T>(*it);
        size_t sz = it - a.begin();
        for (size_t i = 0; i != sz; ++i) {
            tmp *= b;
        }
        ans += tmp;
    }
    return ans;
}

template <typename T>
Polynomial<T> operator & (const T& a, const Polynomial<T>& b) {
    auto newA = Polynomial<T>(a);
    auto ans = Polynomial<T>();
    for (auto it = newA.begin(); it != newA.end(); it++) {
        auto tmp = Polynomial<T>(*it);
        size_t sz = it - newA.begin();
        for (size_t i = 0; i != sz; ++i) {
            tmp *= b;
        }
        ans += tmp;
    }
    return ans;
}

template <typename T>
Polynomial<T> operator & (const Polynomial<T>& a, const T& b) {
    auto newB = Polynomial<T>(b);
    auto ans = Polynomial<T>();
    for (auto it = a.begin(); it != a.end(); it++) {
        auto tmp = Polynomial<T>(*it);
        size_t sz = it - a.begin();
        for (size_t i = 0; i != sz; ++i) {
            tmp *= newB;
        }
        ans += tmp;
    }
    return ans;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Polynomial<T>& polynomial) {
    if (polynomial.Degree() == -1) {
        out << 0;
        return out;
    }
    if (polynomial.size() == 1) {
        out << polynomial[0];
        return out;
    }
    for (auto it = polynomial.rbegin(); it != polynomial.rend(); ++it) {
        if (*it == static_cast<T>(0)) {
            continue;
        }
        if (polynomial.rend() - it == 1) {
            if (*it < T()) {
                out << *it;
            } else {
                out << '+' << *it;
            }
            continue;
        }
        if (*it > static_cast<T>(0)) {
            if (it != polynomial.rbegin()) {
                out << '+';
            }
            if (*it != static_cast<T>(1)) {
                out << *it << '*';
            }
        } else {
            if (*it == static_cast<T>(-1)) {
                out << '-';
            } else {
                out << *it << '*';
            }
        }
        out << 'x';
        if (polynomial.rend() - it != 2) {
            out << '^' << polynomial.rend() - it - 1;
        }
    }
    return out;
}

template <typename T>
Polynomial<T> operator, (const Polynomial<T>&a, const Polynomial<T>& b) {
    auto curA = a, curB = b;
    while (curB.Degree() != -1) {
        curA %= curB;
        auto curT = curA;
        curA = curB;
        curB = curT;
    }
    if (curA.Degree() != -1) {
        Polynomial<T> div(curA[curA.Degree()]);
        curA /= div;
    }
    return curA;
}