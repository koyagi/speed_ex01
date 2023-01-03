#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <cstdlib>

namespace {
    using namespace std::string_literals;
    auto create_akakuro_decks() {
        auto deck_red = std::vector<std::string>{};
        auto deck_black = std::vector<std::string>{};
        deck_red.reserve(26);
        deck_black.reserve(26);
        const auto suits_red = std::vector<std::string>{ "D"s, "H"s };
        const auto suits_black = std::vector<std::string>{ "S"s, "C"s };
        const auto rank = std::vector<std::string>{"A"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s, "10"s, "J"s, "Q"s, "K"s};
        for(int i = 0; i < 26; i++) {
            deck_red.push_back(suits_red.at(i / 13) + rank.at(i % 13));
        }
        for(int i = 0; i < 26; i++) {
            deck_black.push_back(suits_black.at(i / 13) + rank.at(i % 13));
        }
        return std::make_tuple(deck_red, deck_black);
    }
}



int main() {
    using namespace std::string_literals;
    std::cout << "howdy!"s << std::endl;

    auto [pile_red, pile_black] = create_akakuro_decks();

    for(const auto el : pile_red ) {
        std::cout << el << ", ";
    }
    std::cout << std::endl;
    for(const auto el : pile_black ) {
        std::cout << el << ", ";
    }
    std::cout << std::endl;
    std::cout << "bye!"s << std::endl;
    return EXIT_SUCCESS;
}