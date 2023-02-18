#include <algorithm>
#include <unordered_map>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include <nlohmann/json.hpp>

#include "mysafestack.hpp"

namespace {
    using namespace std::string_literals;
    using strVec = std::vector<std::string>;
    using strStack = MySafeStack<strVec::value_type, strVec>;
    using strSet = std::set<std::string>;

    template <typename T, typename S>
    auto recreateDataSetAs(const S & src) -> T {
        using std::begin;
        using std::end;
        return T(begin(src), end(src));
    }

    auto create_half_deck(const strVec & suits) {    // Here, "const &" is better than universal-refarence.
        const auto rank = strVec{"A"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s, "10"s, "J"s, "Q"s, "K"s};
        auto deck = strVec{};
        deck.reserve( suits.size() * rank.size() );
        for(const auto & aSuit : suits) {
            std::transform(std::cbegin(rank), std::cend(rank), std::back_inserter(deck),
                [suit = aSuit](std::string aRank){return suit + aRank;}
            );
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
        return std::make_tuple(MySafeStack(deck_red), MySafeStack(deck_black));
    }

    class GameTable {
    public:
        enum class Player {
            RED,
            BLACK
        };
        GameTable() {
            std::tie(stock.at(GameTable::Player::RED), stock.at(GameTable::Player::BLACK)) = create_akakuro_decks();
        }

        GameTable(std::string debug_init) {
            using json = nlohmann::json;
            auto j = json::parse(debug_init);

            stock.at(GameTable::Player::RED) = recreateDataSetAs<strStack>(j.at("redStock"));
            stock.at(GameTable::Player::BLACK) = recreateDataSetAs<strStack>(j.at("blackStock"));
            redUpcard = recreateDataSetAs<strSet>(j.at("redUpcard"));
            blackUpcard = recreateDataSetAs<strSet>(j.at("blackUpcard"));
            redSidePile = recreateDataSetAs<strVec>(j.at("redSidePile"));
            blackSidePile = recreateDataSetAs<strVec>(j.at("blackSidePile"));
        }

        auto getPrivate() {
            return std::make_tuple(stock.at(GameTable::Player::RED), stock.at(GameTable::Player::BLACK));
        }
        
        auto getDebugInfo() -> std::string {
            using json = nlohmann::json;
            json j{};

            j["redStock"] = stock.at(GameTable::Player::RED).getUnderlyingContainer();
            j["blackStock"] = stock.at(GameTable::Player::BLACK).getUnderlyingContainer();
            j["redUpcard"] = redUpcard;
            j["blackUpcard"] = blackUpcard;
            j["redSidePile"] = redSidePile;
            j["blackSidePile"] = blackSidePile;

            return j.dump();
        }

    // void turnup( GameTable::Player pl) {

    // }

    private:
        std::unordered_map<GameTable::Player, strStack> stock = {
            {GameTable::Player::RED, strStack{}},
            {GameTable::Player::BLACK, strStack{}}
        };
        strSet redUpcard{};
        strSet blackUpcard{};
        strVec redSidePile{};
        strVec blackSidePile{};
    };
}
