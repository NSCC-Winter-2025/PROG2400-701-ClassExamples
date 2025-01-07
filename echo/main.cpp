#include <iostream>
#include <string_view>

using namespace std::literals;

int main() {
  constexpr auto END = "end"sv;

  const auto get_input = []() {
    std::string input;
    std::cout << "Enter a line of text: "sv;
    std::getline(std::cin, input);
    return input;
  };

  std::string user_input;
  while ((user_input = get_input()) != END) {
    std::cout << R"(You typed: ")"sv << user_input << R"(")"sv << std::endl;
  }
}
