#include <iostream>

int main() {
    int n;
    size_t i;
    std::cin >> n >> i;
    int newN = (1 << i);
    std::cout << (n ^ newN) << '\n';
}
