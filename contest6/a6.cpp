#include <iostream>
#include <string>

int64_t check_str(std::string & s) {
    size_t i = 0;
    if ((s[i] >> 7) & 1) {
         if ((s[i] >> 6) & 1) {
            if ((s[i] >> 5) & 1) {
                if ((s[i] >> 4) & 1) {
                    int64_t getAns = (s[i] & ((1 << 3) - 1));
                    getAns <<= 6;
                    for (size_t j = 1; j != 4; ++j) {
                        getAns += (s[i + j] & ((1 << 6) - 1));
                        if (j != 3) {
                            getAns <<= 6;
                        }
                    }
                    return getAns;
                }
                int64_t getAns = (s[i] & ((1 << 4) - 1));
                getAns <<= 6;
                for (size_t j = 1; j != 3; ++j) {
                    getAns += (s[i + j] & ((1 << 6) - 1));
                    if (j != 2) {
                        getAns <<= 6;
                    }
                }
                return getAns;
            }
            int64_t getAns = (s[i] & ((1 << 5) - 1));
            getAns <<= 6;
            getAns += (s[i + 1] & ((1 << 6) - 1));
            return getAns;
        }
    } else {
        return int64_t(s[i]);
    }
}

std::string gen(int type, int64_t x) {
    std::string ret = "";
    if (type == 0) {
        for (int i = 0; i != (1 << 7); ++i) {
            ret = "";
            ret += static_cast<char>(i);
            if (check_str(ret) == x) {
                return ret;
            }
            ret.pop_back();
        }
    } else if (type == 1) {
        for (int i = 0; i != (1 << 5); ++i) {
            ret = "";
            char c = static_cast<char>(6);
            c <<= 5;
            ret += static_cast<char>(c + i);
            for (int j = 0; j != (1 << 6); ++j) {
                char q = static_cast<char>(2);
                q <<= 6;
                ret += static_cast<char>(q + j);
                if (check_str(ret) == x) {
                    return ret;
                }
                ret.pop_back();
            }
            ret.pop_back();
        }
    } else if (type == 2) {
        for (int i = 0; i != (1 << 4); ++i) {
            ret = "";
            char c1 = static_cast<char>(14);
            c1 <<= 4;
            ret += static_cast<char>(c1 + i);
            for (int j = 0; j != (1 << 6); ++j) {
                char c2 = static_cast<char>(2);
                c2 <<= 6;
                ret += static_cast<char>(c2 + j);
                for (int y = 0; y != (1 << 6); ++y) {
                    char c3 = static_cast<char>(2);
                    c3 <<= 6;
                    ret += static_cast<char>(c3 + y);
                    if (check_str(ret) == x) {
                        return ret;
                    }
                    ret.pop_back();
                }
                ret.pop_back();
            }
            ret.pop_back();
        }
    } else if (type == 3) {
        for (int i = 0; i != (1 << 3); ++i) {
            ret = "";
            char c1 = static_cast<char>(30);
            c1 <<= 3;
            ret += static_cast<char>(c1 + i);
            for (int j = 0; j != (1 << 6); ++j) {
                char c2 = static_cast<char>(2);
                c2 <<= 6;
                ret += static_cast<char>(c2 + j);
                for (int y = 0; y != (1 << 6); ++y) {
                    char c3 = static_cast<char>(2);
                    c3 <<= 6;
                    ret += static_cast<char>(c3 + y);
                    for (int t = 0; t != (1 << 6); ++y) {
                        char c4 = static_cast<char>(2);
                        c4 <<= 6;
                        ret += static_cast<char>(c4 + t);
                        if (check_str(ret) == x) {
                            return ret;
                        }
                        ret.pop_back();
                    }
                    ret.pop_back();
                }
                ret.pop_back();
            }
            ret.pop_back();
        }
    }
    return ret;
}
int main() {
    int64_t x;
    while (std::cin >> x) {
        for (int i = 0; i != 4; ++i) {
            std::string generat = gen(i, x);
            if (check_str(generat) == x) {
                std::cout << generat;
                break;
            }
        }
    }
}
