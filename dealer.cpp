#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>



int main() {
    using namespace std::string_literals;
    std::cout << "howdy!"s << std::endl;

    const auto suits_red = std::vector<std::string>{ "D"s, "H"s };
    const auto suits_black = std::vector<std::string>{ "S"s, "C"s };
    const auto number = std::vector<std::string>{"A"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s, "10"s, "J"s, "Q"s, "K"s};
    auto deck_red = std::vector<std::string>{};
    deck_red.reserve(26);
    auto deck_black = std::vector<std::string>{};
    deck_black.reserve(26);
    for(int i = 0; i < 26; i++) {
        deck_red.push_back(suits_red.at(i / 13) + number.at(i % 13));
    }
    for(int i = 0; i < 26; i++) {
        deck_black.push_back(suits_black.at(i / 13) + number.at(i % 13));
    }
    for(const auto el : deck_red ) {
        std::cout << el << ", ";
    }
    std::cout << std::endl;
    for(const auto el : deck_black ) {
        std::cout << el << ", ";
    }
    std::cout << std::endl;
    std::cout << "bye!"s << std::endl;
    return EXIT_SUCCESS;
}