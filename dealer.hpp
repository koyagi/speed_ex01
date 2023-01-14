#include <algorithm>
#include <random>
#include <string>
#include <tuple>
#include <vector>

namespace {
    using namespace std::string_literals;
    using strVec = std::vector<std::string>;

    template<typename T = const strVec>
    auto create_half_deck( T && suits) {    // Here, argument suits should be const universal-refarence.
        const auto rank = strVec{"A"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s, "10"s, "J"s, "Q"s, "K"s};
        auto deck = strVec{};
        deck.reserve( suits.size() * rank.size() );
        for(const auto & aSuit : suits) {
            std::transform(std::cbegin(rank), std::cend(rank), std::back_inserter(deck), [suit = aSuit](std::string aRank){return suit + aRank;});
        }
        return deck;
    }

    void cardShuffle(strVec & deck) {
        std::random_device seed;
        std::mt19937_64 randomEngine(seed());
        std::shuffle(std::begin(deck), std::end(deck), randomEngine);
    }

    auto create_akakuro_decks() {
        auto deck_red = create_half_deck({ "D"s, "H"s });
        auto deck_black = create_half_deck({ "S"s, "C"s });
        cardShuffle(deck_red);
        cardShuffle(deck_black);
        return std::make_tuple(deck_red, deck_black);
    }
}
