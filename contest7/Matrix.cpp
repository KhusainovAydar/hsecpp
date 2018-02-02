#include <iostream>
#include <vector>

template<typename T>
class Matrix;


template<typename T>
class Matrix {
  private:
    std::vector<std::vector<T>> data;

  public:
    Matrix(const std::vector<std::vector<T>>& matrix)
        : data(matrix) {}

    T operator() (size_t i, size_t j) const {
        return data[i][j];
    }

    std::pair<size_t, size_t> size() const {
        if (data.empty()) {
            return {0, 0};
        }
        return {data.size(), data[0].size()};
    }

    Matrix& operator += (const Matrix<T>& other) {
        auto sz = size();
        for (size_t i = 0; i != sz.first; ++i) {
            for (size_t j = 0; j != sz.second; ++j) {
                data[i][j] += other(i, j);
            }
        }
        return *this;
    }

    Matrix operator + (const Matrix<T>& other) const {
        auto P = *this;
        P += other;
        return P;
    }

    template<typename newT>
    Matrix& operator *= (const newT& con) {
        auto sz = size();
        for (size_t i = 0; i != sz.first; ++i) {
            for (size_t j = 0; j != sz.second; ++j) {
                data[i][j] *= con;
            }
        }
        return *this;
    }

    template<typename newT>
    Matrix operator * (const newT& con) const {
        auto P = *this;
        P *= con;
        return P;
    }

    Matrix& transpose() {
        auto sz = size();
        std::vector<std::vector<T>> matrix(sz.second, std::vector<T>(sz.first));
        for (size_t i = 0; i != sz.first; ++i) {
            for (size_t j = 0; j != sz.second; ++j) {
                matrix[j][i] = data[i][j];
            }
        }
        *this = Matrix(matrix);
        return *this;
    }

    Matrix transposed() const {
        auto P = *this;
        P.transpose();
        return P;
    }

    Matrix& operator *= (const Matrix & other) {
        auto sz = size();
        size_t n = sz.second;
        sz.second = other.size().second;
        std::vector<std::vector<T>> C(sz.first, std::vector<T> (sz.second));
        for (size_t i = 0; i != sz.first; ++i) {
            for (size_t j = 0; j != sz.second; ++j) {
                for (size_t y = 0; y != n; ++y) {
                    C[i][j] += data[i][y] * other(y, j);
                }
            }
        }
        *this = Matrix(C);
        return *this;
    }

    Matrix operator * (const Matrix& other) {
        auto C = *this;
        C *= other;
        return C;
    }

    template<bool isConst>
    class RowIterator {
      public:
        using returnT = typename std::conditional<isConst, const T&, T>::type;
        using matrixT = typename std::conditional<isConst, const Matrix<T>*, Matrix<T>*>::type;

        RowIterator(matrixT _matrix, size_t _row, size_t _column)
            : matrix(_matrix)
            , row(_row)
            , column(_column) {}

        RowIterator(matrixT _matrix)
            : matrix(_matrix) {
            row = matrix->size().first;
            column = 0;
        }

        returnT operator * () {
            return matrix->data[row][column];
        }

        RowIterator& operator++ () {
            ++column;
            if (column == matrix->size().second) {
                column = 0;
                ++row;
            }
            return *this;
        }

        RowIterator operator++ (int) {
            auto temp = *this;
            ++*this;
            return temp;
        }

        bool operator == (RowIterator other) const {
            return row == other.row && column == other.column;
        }

        bool operator != (RowIterator other) const {
            return !(*this == other);
        }

        private:
          matrixT matrix;
          size_t row;
          size_t column;
    };

    using Iterator = RowIterator<false>;
    using ConstIterator = RowIterator<1>;

    Iterator begin() {
        return Iterator(this, 0, 0);
    }

    Iterator end() {
        return Iterator(this);
    }

    ConstIterator begin() const {
        return ConstIterator(this, 0, 0);
    }

    ConstIterator end() const {
        return ConstIterator(this);
    }

    template<typename U>
    std::vector<U> solve(const std::vector<U>& b) {
        size_t n = size().first;
        std::vector<std::vector<U>> matrix(n, std::vector<U>(n));
        for (size_t i = 0; i != n; ++i) {
            for (size_t j = 0; j != n; ++j) {
                matrix[i][j] = data[i][j];
            }
        }
        std::vector<U> ans = b;
        for (size_t i = 0; i != n; ++i) {
            U val = matrix[i][i];
            for (size_t j = i; j != n; ++j) {
                if (matrix[j][i] > matrix[i][i]) {
                    for (size_t q = 0; q != n; ++q) {
                        auto tmp = matrix[j][q];
                        matrix[j][q] = matrix[i][q];
                        matrix[i][q] = tmp;
                    }
                    auto tmp = ans[i];
                    ans[i] = ans[j];
                    ans[j] = tmp;
                }
            }
            val = matrix[i][i];
            for (size_t j = 0; j != n; ++j) {
                if (j == i) {
                    continue;
                }
                U coef = matrix[j][i];
                for (size_t q = 0; q != n; ++q) {
                    matrix[j][q] = matrix[j][q] * val - matrix[i][q] * coef;
                }
                ans[j] = (ans[j] * val - ans[i] * coef);
            }
        }
        for (size_t i = 0; i != n; ++i) {
            ans[i] /= matrix[i][i];
            if (ans[i] == -0) {
                ans[i] = 0;
            }
        }
        return ans;
    }
};

template<typename T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& m) {
    std::pair<size_t, size_t> sz = m.size();
    for (size_t i = 0; i != sz.first; ++i) {
        for (size_t j = 0; j != sz.second; ++j) {
            if (j > 0) {
                out << '\t';
            }
            out << m(i, j);
        }
        if (i != sz.first - 1) {
            out << '\n';
        }
    }
    return out;
}





