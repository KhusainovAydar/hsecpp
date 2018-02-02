#include <iostream>

int main() {
    uint64_t x;
    std::cin >> x;
    std::cout << __builtin_popcountll(static_cast<uint64_t>(x)) << '\n';
}
