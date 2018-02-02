#include <iostream>

int main() {
    int n;
    size_t i;
    std::cin >> n >> i;
    std::cout << (n & ((1 << i) - 1)) << '\n';
}
