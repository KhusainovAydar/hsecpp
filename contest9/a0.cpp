#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> data;

public:
    Matrix(const std::vector<std::vector<int>>& matrix)
        : data(matrix) {
        for (size_t i = 1; i < matrix.size(); ++i) {
            if (matrix[0].size() != matrix[i].size()) {
                throw std::length_error("constructor row length error");
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < size().second; ++j) {
                if (j > 0) {
                    std::cout << '\t';
                }
                std::cout << data[i][j];
            }
            std::cout << '\n';
        }
    }

    std::pair<size_t, size_t> size() const {
        if (data.empty()) {
            return {0, 0};
        }
        return {data.size(), data[0].size()};
    }



    int get_elem(int row, int col) const {
        if (0 > row || row >= static_cast<int>(size().first) || 0 > col ||
                col >= static_cast<int>(size().second)) {
            throw std::out_of_range("get_elem bad indices");
        }
        return data[row][col];
    }

    Matrix operator + (const Matrix& other) const {
        if (size() != other.size()) {
            throw std::length_error("operator+ size error");
        }
        std::vector<std::vector<int>> summary(size().first, std::vector<int> (size().second));
        for (size_t i = 0; i < size().first; ++i) {
            for (size_t j = 0; j < size().second; ++j) {
                summary[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return Matrix(summary);
    }
};