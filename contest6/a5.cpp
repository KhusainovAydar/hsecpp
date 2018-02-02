#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);
    int ans = 0;
    for (size_t i = 0; i != s.length(); ++i) {
        if ((s[i] >> 7) & 1) {
            if ((s[i] >> 6) & 1) {
                if ((s[i] >> 5) & 1) {
                    if ((s[i] >> 4) & 1) {
                        
                        i += 3;
                        ++ans;
                        continue;
                    }
                    i += 2;
                    ++ans;
                    continue;
                }
                int getAns = (s[i] & (1 << 6 - 1));
                for (size_t j = 0; j != 8; ++j) {
                    std::cout << ((getAns >> j) & 1);
                }
                std::cout << '\n';
                i += 1;
                ++ans;
                continue;
            }
        } else {
            std::cout << int(s[i]) << ' ';
        }
    }
}
