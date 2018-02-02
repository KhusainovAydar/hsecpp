#include <iostream>

int main() {
    int n;
    size_t i;
    std::cin >> n >> i;
    std::cout << ((n >> i) & 1) << '\n';
}
