#include <iostream>
#include <string>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::string> arr(n);
    for (size_t i = 0; i != n; ++i) {
        std::cin >> arr[i];
    }
    for (int32_t i = 0; i != (1 << n); ++i) {
        bool first = true;
        std::cout << '[';
        for (size_t j = 0; j != n; ++j) {
            if ((i >> j) & 1) {
                if (first) {
                    first = false;
                } else {
                    std::cout << ',';
                }
                std::cout << arr[j];
            }
        }
        std::cout << ']' << '\n';
    }
}
