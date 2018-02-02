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
