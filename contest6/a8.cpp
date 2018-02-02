#include <iostream>
#include <vector>

int main() {
    size_t n, m;
    std::cin >> n >> m;
    std::vector<int32_t> v(n);
    for (size_t i = 0; i != n; ++i) {
        v[i] = 0;
        for (size_t j = 0; j != m; ++j) {
            int32_t y;
            std::cin >> y;
            v[i] <<= 1;
            v[i] += y;
        }
    }
    int32_t ans = 0;
    for (int32_t i = 0; i != (1 << n); ++i) {
        int32_t sum = 0;
        for (size_t j = 0; j != n; ++j) {
            if ((i >> j) & 1)
                sum |= v[j];
        }
        if (sum == (1 << m) - 1) {
            ++ans;
        }
    }
    std::cout << ans << '\n';
}
