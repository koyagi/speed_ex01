#include <algorithm>
#include <random>
#include <string>
#include <tuple>
#include <vector>

namespace {
    using namespace std::string_literals;

    auto create_half_deck(const auto && suits) {
        const auto rank = std::vector<std::string>{"A"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s, "10"s, "J"s, "Q"s, "K"s};
        auto deck = std::vector<std::string>{};
        deck.reserve(26);
        std::transform(std::begin(rank), std::end(rank), std::back_inserter(deck), [suit = suits.at(0)](std::string aRank){return suit + aRank;});
        std::transform(std::begin(rank), std::end(rank), std::back_inserter(deck), [suit = suits.at(1)](std::string aRank){return suit + aRank;});
        return deck;
    }

    void cardShuffle(std::vector<std::string> & deck) {
        std::random_device seed;
        std::mt19937_64 randomEngine(seed());
        std::shuffle(std::begin(deck), std::end(deck), randomEngine);
    }

    auto create_akakuro_decks() {   // FIXME: need refactoring
        const auto suits_red = std::vector<std::string>{ "D"s, "H"s };
        const auto suits_black = std::vector<std::string>{ "S"s, "C"s };
        auto deck_red = create_half_deck(suits_red);
        auto deck_black = create_half_deck(suits_black);
        cardShuffle(deck_red);
        cardShuffle(deck_black);
        return std::make_tuple(deck_red, deck_black);
    }
}
