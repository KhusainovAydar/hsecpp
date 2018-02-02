#include <iostream>

int main() {
    uint32_t n;
    std::cin >> n;
    size_t maxIt = 0;
    for (size_t i = 0; i != 16; ++i) {
        if ((n >> i) & 1) {
            maxIt = std::max(maxIt, i);
        }
    }
    uint32_t maxAns = n;
    for (size_t i = 0; i != maxIt; ++i) {
        n += ((n & 1) << (maxIt + 1));
        n >>= 1;
        maxAns = std::max(n, maxAns);
    }
    std::cout << maxAns << '\n';
}
