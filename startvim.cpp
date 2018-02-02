#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>

void sortLibrary() {
    std::vector<std::string> libraries;
    std::string kek, lol;
    while (std::cin >> kek >> lol) {
        libraries.push_back(lol);
    }
    std::sort(libraries.begin(), libraries.end());
    for (auto& t : libraries) {
        std::cout << "#include " << t << '\n';
    }
    exit(0);
}

template <typename InIter1, typename InIter2, typename OutIter>
OutIter set_difference(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2, OutIter out) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 == *first2) {
            ++first1;
            ++first2;
        } else if (*first1 < *first2) {
            *out = *first1;
            ++out;
            ++first1;
        } else {
            ++first2;
        }
    }
    while (first1 != last1) {
        *out = *first1;
        ++out;
        ++first1;
    }
    return out;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<int> a(n);
    for (size_t i = 0; i != n; ++i) {
        std::cin >> a[i];
    }
    size_t m;
    std::cin >> m;
    std::vector<int> b(m);
    for (size_t i = 0; i != m; ++i) {
        std::cin >> b[i];
    }
    std::vector<int> c;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(c));
    for (auto& t : c) {
        std::cout << t << ' ';
    }
    std::cout << '\n';
}
