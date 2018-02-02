#include <iostream>
#include <vector>
#include <map>
#include <assert.h>

template<typename T>
class Polynomial {
private:
    std::map<size_t, T> arrPolynomial;
    using ConstIter = typename std::map<size_t, T>::const_iterator;
    using ConstRevIter = typename std::map<size_t, T>::const_reverse_iterator;
    T TypeDefVal;
    void clearZero() {
        for (auto it = arrPolynomial.begin(); it != arrPolynomial.end();) {
            if (it->second == T()) {
                it = arrPolynomial.erase(it);
            } else {
                ++it;
            }
        }
    }
    Polynomial operator << (size_t k) const {
        Polynomial ret;
        for (auto i = arrPolynomial.begin(); i != arrPolynomial.end(); ++i) {
            ret.arrPolynomial[i->first + k] = i->second;
        }
        return ret;
    }

    T bPow(const T&x, size_t k) const {
        if (k == 0) {
            return 1;
        }
        T ans = 1;
        T cur = x;
        while (k) {
            if (k % 2 == 0) {
                k /= 2;
                cur *= cur;
            } else {
                --k;
                ans *= cur;
            }
        }
        return ans;
    }


public:
    Polynomial<T>(const std::vector<T>& arr) {
        for (size_t i = 0; i != arr.size(); ++i) {
            arrPolynomial[i] = arr[i];
        }
        TypeDefVal = T();
        clearZero();
    }

    Polynomial<T>(const T& x = T()) {
        arrPolynomial[0] = x;
        TypeDefVal = T();
        clearZero();
    }

    template <typename Iter>
    Polynomial<T>(Iter begin, Iter end) {
        arrPolynomial.clear();
        size_t i = 0;
        while (begin != end) {
            arrPolynomial[i++] = *begin++;
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
        return arrPolynomial.rbegin()->first;
    }

    const T& operator[] (size_t id) const {
        if (arrPolynomial.count(id)) {
            return arrPolynomial.at(id);
        }
        return TypeDefVal;
    }

    size_t size() const {
        return arrPolynomial.size();
    }


    Polynomial& operator += (const Polynomial& other) {
        for (auto i = other.arrPolynomial.cbegin();
                i != other.arrPolynomial.cend(); ++i) {
            arrPolynomial[i->first] += i->second;
        }
        clearZero();
        return *this;
    }

    Polynomial& operator -= (const Polynomial& other) {
        for (auto i = other.arrPolynomial.cbegin();
             i != other.arrPolynomial.cend(); ++i) {
            arrPolynomial[i->first] -= i->second;
        }
        clearZero();
        return *this;
    }

    Polynomial& operator *= (const Polynomial& other) {
        Polynomial<T> ans;
        for (auto it1 = arrPolynomial.begin();
             it1 != arrPolynomial.end();
             ++it1) {
            for (auto it2 = other.arrPolynomial.begin();
                 it2 != other.arrPolynomial.end();
                 ++it2) {
                ans.arrPolynomial[it1->first + it2->first] +=
                        it1->second * it2->second;
            }
        }
        *this = ans;
        clearZero();
        return *this;
    }

    Polynomial& operator /= (const Polynomial& other) {
        Polynomial<T> quetient, remainder = *this;
        while (remainder.Degree() >= other.Degree()) {
            T coef = remainder.rbegin()->second / other.rbegin()->second;
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
        size_t cnt = 0;
        for (auto it = arrPolynomial.begin();
             it != arrPolynomial.end();
             ++it) {
            curPow *= bPow(x, it->first - cnt);
            cnt = it->first;
            ans += it->second * curPow;
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
        auto tmp = Polynomial<T>(it->second);
        for (size_t i = 0; i != it->first; ++i) {
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
        auto tmp = Polynomial<T>(it->second);
        for (size_t i = 0; i != it->first; ++i) {
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
        auto tmp = Polynomial<T>(it->second);
        for (size_t i = 0; i != it->first; ++i) {
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
    if (polynomial.rbegin()->first == 0) {
        out << polynomial[0];
        return out;
    }
    for (auto it = polynomial.rbegin(); it != polynomial.rend(); ++it) {
        if (it->first == 0) {
            if (it->second < T()) {
                out << it->second;
            } else {
                out << '+' << it->second;
            }
            continue;
        }
        if (it->second > static_cast<T>(0)) {
            if (it != polynomial.rbegin()) {
                out << '+';
            }
            if (it->second != static_cast<T>(1)) {
                out << it->second << '*';
            }
        } else {
            if (it->second == static_cast<T>(-1)) {
                out << '-';
            } else {
                out << it->second << '*';
            }
        }
        out << 'x';
        if (it->first != 1) {
            out << '^' << it->first;
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