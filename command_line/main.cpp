#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char** argv, char** envp) {
    // output command line arguments
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    for (const auto& arg : args) {
        std::cout << arg << std::endl;
    }

    // output environment variables
    std::stringstream ss;
    std::string name, value;
    for (auto e = envp; *e != nullptr; e++) {
        ss.clear();
        ss << *e;
        std::getline(ss, name, '=');
        std::getline(ss, value);
        if (name == "THEME") {
            std::cout << *e << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Value: " << value << std::endl;
        }
    }

    return 0;
}
