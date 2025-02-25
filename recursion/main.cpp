#include <iostream>
#include <filesystem>
#include <queue>

namespace fs = std::filesystem;

void list_folders_recursive(const fs::path& path, int indent = 0) {
    // recursively list folder names
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            const auto& subpath = entry.path();
            std::cout << std::string(indent, ' ') << subpath << "\n";
            list_folders_recursive(subpath, indent + 2);
        }
    }
}

void list_folders(const fs::path& path, int indent = 0) {
    std::queue<std::pair<fs::path, int>> paths;

    // recursively list folder names
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            paths.emplace(entry.path(), 0);
        }
    }

    while (!paths.empty()) {
        // pop one folder off queue and go into that folder
        auto current = paths.front();
        std::cout << std::string(current.second, ' ') << current.first << "\n";
        paths.pop();

        // push folders in current folder on to queue
        for (const auto& entry : fs::directory_iterator(current.first)) {
            if (entry.is_directory()) {
                paths.emplace(entry.path(), current.second + 2);
            }
        }
    }
}

int main() {
    auto path = fs::path("..");

    std::cout << std::endl;
    std::cout << "Recursive..." << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << std::endl;

    list_folders_recursive(path);

    std::cout << std::endl;
    std::cout << "Non-Recursive..." << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;

    list_folders(path);

    return 0;
}

