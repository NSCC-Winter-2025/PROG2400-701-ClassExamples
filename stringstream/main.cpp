#include <iostream>
#include <sstream>

void cin_version() {
    char command;
    int start, end;

    std::cout << "Enter a command and two numbers: ";
    std::cin >> command >> start >> end;

    std::cout << "command: " << command;
    std::cout << ", start: " << start;
    std::cout << ", end: " << end << std::endl;
}

void stringstream_version() {
    std::string command = "X";

    std::string user_input;
    std::cout << "Enter a command and two numbers: ";
    std::getline(std::cin, user_input);

    std::stringstream ss(user_input);
    ss >> command;

    if (command.length() > 1) {
        std::cout << "You entered some text: " << user_input << std::endl;
    }
    else {
        std::cout << "Maybe you typed in a command." << std::endl;

        int start = -1;
        ss >> start;
        if (ss.fail()) {
            std::cout << "Ah! You entered in something that LOOKED like a command: " << user_input << std::endl;
            return;
        }

        int end = -1;
        if (!ss.eof()) {
            ss >> end;
            if (ss.fail()) {
                std::cout << "You tricky bugger...that is just TEXT!: " << user_input << std::endl;
                return;
            }
        }

        std::string extra;
        if (!ss.eof()) {
            ss >> extra;
            if (extra.length() > 1) {
                std::cout << "It kinda looks like a command, but I'll assume it isn't: " << user_input << std::endl;
                return;
            }
        }

        std::cout << "user_input: " << user_input << std::endl;
        std::cout << "command: " << command;
        std::cout << ", start: " << start;
        std::cout << ", end: " << end << std::endl;
    }
}

int main() {
    stringstream_version();

    return 0;
}
