#include <iostream>
#include <cstring>

bool is_palindrome(const char* input, const size_t length) {
    for (auto i = 0; i < length / 2; i++) {
        if (input[i] != input[length - i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_palindrome_recursive(const char* input, size_t len) {
    // end condition
    if (len <= 1) return true;
    // compare first and last letters
    if (input[0] == input[len - 1]) {
        // could be a palindrome
        // check the next set of characters
        return is_palindrome_recursive(&input[1], len - 2);
    }
    return false;
}

bool is_palindrome(std::string_view input) {
    while (input.size() > 1) {
        if (input[0] != input[input.size() - 1]) { return false; }
        input = std::string_view(input.data() + 1, input.length() - 2);
    }
    return true;
}

// tail call recursion (TCO) (GOOD)
bool is_palindrome_recursive2(std::string_view input) {
    // strings that have only 1 letter (or no letters) can be assumed to be a palindrome
    if (input.length() <= 1) return true;
    // compare first and last letters
    if (*input.begin() == *input.rbegin()) {
        return is_palindrome_recursive2({input.data() + 1, input.length() - 2});
    }
    return false;
}

// head end recursion (BAD)
bool is_palindrome_recursive3(std::string_view input) {
    if (input.length() <= 1) return true;
    if (is_palindrome_recursive3({input.data() + 1, input.length() - 2})) {
        return *input.begin() == *input.rbegin();
    }
    return false;
}

bool is_palindrome2(std::string_view input) {
    return input == std::string(input.rbegin(), input.rend());
}

int main() {
    constexpr auto BUFFER_SIZE = 80uz;
    char input[BUFFER_SIZE];

    std::cout << "Enter a word: ";
    std::cin.getline(input, BUFFER_SIZE);

    std::cout << "c-string version" << std::endl;
    if (is_palindrome(input, strnlen(input, BUFFER_SIZE))) {
        std::cout << input << " IS a palindrome." << std::endl;
    } else {
        std::cout << input << " is NOT a palindrome." << std::endl;
    }

    std::cout << "string_view version" << std::endl;
    if (is_palindrome(input)) {
        std::cout << input << " IS a palindrome." << std::endl;
    } else {
        std::cout << input << " is NOT a palindrome." << std::endl;
    }

    std::cout << "reverse iterator version" << std::endl;
    if (is_palindrome2(input)) {
        std::cout << input << " IS a palindrome." << std::endl;
    } else {
        std::cout << input << " is NOT a palindrome." << std::endl;
    }

    std::cout << "\nrecursive c-string version" << std::endl;
    if (is_palindrome_recursive(input, strnlen(input, BUFFER_SIZE))) {
        std::cout << input << " IS a palindrome." << std::endl;
    } else {
        std::cout << input << " IS NOT a palindrome." << std::endl;
    }

    std::cout << "\nrecursive reversed string version" << std::endl;
    if (is_palindrome_recursive2(input)) {
        std::cout << input << " IS a palindrome." << std::endl;
    } else {
        std::cout << input << " IS NOT a palindrome." << std::endl;
    }

    std::cout << "\nhead end recursion version" << std::endl;
    if (is_palindrome_recursive3(input)) {
        std::cout << input << " IS a palindrome." << std::endl;
    } else {
        std::cout << input << " IS NOT a palindrome." << std::endl;
    }

    return 0;
}
