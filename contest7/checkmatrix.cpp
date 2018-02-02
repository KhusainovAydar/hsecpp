
int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::vector<int>> arr(n, std::vector<int> (n));
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != n; ++j) {
            std::cin >> arr[i][j];
        }
    }
    std::vector<double> b(n);
    for (size_t i = 0; i != n; ++i) {
        std::cin >> b[i];
    }
    Matrix<int> mt(arr);
    std::vector<double> ans = mt.solve(b);
    for (size_t i = 0; i != n; ++i) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
}
