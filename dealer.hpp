

#include <string>
#include <tuple>
#include <vector>

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
