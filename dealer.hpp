#include <algorithm>
#include <random>
#include <string>
#include <tuple>
#include <vector>

namespace {
    using namespace std::string_literals;

    void cardShuffle(std::vector<std::string> & deck) {
        std::random_device seed;
        std::mt19937_64 randomEngine(seed());
        std::shuffle(std::begin(deck), std::end(deck), randomEngine);
    }

    auto create_akakuro_decks() {   // FIXME: need refactoring
        auto deck_red = std::vector<std::string>{};
        auto deck_black = std::vector<std::string>{};
        deck_red.reserve(26);
        deck_black.reserve(26);
        const auto suits_red = std::vector<std::string>{ "D"s, "H"s };
        const auto suits_black = std::vector<std::string>{ "S"s, "C"s };
        const auto rank = std::vector<std::string>{"A"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s, "10"s, "J"s, "Q"s, "K"s};
        std::transform(std::begin(rank), std::end(rank), std::back_inserter(deck_red), [suit = suits_red.at(0)](std::string aRank){return suit + aRank;});
        std::transform(std::begin(rank), std::end(rank), std::back_inserter(deck_red), [suit = suits_red.at(1)](std::string aRank){return suit + aRank;});
        std::transform(std::begin(rank), std::end(rank), std::back_inserter(deck_black), [suit = suits_black.at(0)](std::string aRank){return suit + aRank;});
        std::transform(std::begin(rank), std::end(rank), std::back_inserter(deck_black), [suit = suits_black.at(1)](std::string aRank){return suit + aRank;});
        // for(int i = 0; i < 26; i++) {
        //     deck_red.push_back(suits_red.at(i / 13) + rank.at(i % 13));
        // }
        // for(int i = 0; i < 26; i++) {
        //     deck_black.push_back(suits_black.at(i / 13) + rank.at(i % 13));
        // }
        cardShuffle(deck_red);
        cardShuffle(deck_black);
        return std::make_tuple(deck_red, deck_black);
    }
}
