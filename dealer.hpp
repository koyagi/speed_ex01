#include <algorithm>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include <nlohmann/json.hpp>

namespace {
    using namespace std::string_literals;
    using strVec = std::vector<std::string>;

    template<typename T = const strVec>
    auto create_half_deck( T && suits) {    // Here, argument suits should be const universal-refarence.
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
        return std::make_tuple(deck_red, deck_black);
    }
    class GameTable {
    public:
        GameTable() {
            std::tie(redStock, blackStock) = create_akakuro_decks();
        }

        GameTable(std::string debug_init) {
            using json = nlohmann::json;
            auto j = json::parse(debug_init);

            auto tmp_redStock = j.at("redStock");
            auto tmp_blackStock = j.at("blackStock");
            auto tmp_redUpcard = j.at("redUpcard");
            auto tmp_blackUpcard = j.at("blackUpcard");
            auto tmp_redSidePile = j.at("redSidePile");
            auto tmp_blackSidePile = j.at("blackSidePile");

            redStock = strVec(std::begin(tmp_redStock),std::end(tmp_redStock));
            blackStock = strVec(std::begin(tmp_blackStock),std::end(tmp_blackStock));
            redUpcard = strVec(std::begin(tmp_redUpcard),std::end(tmp_redUpcard));
            blackUpcard = strVec(std::begin(tmp_blackUpcard),std::end(tmp_blackUpcard));
            redSidePile = strVec(std::begin(tmp_redSidePile),std::end(tmp_redSidePile));
            blackSidePile = strVec(std::begin(tmp_blackSidePile),std::end(tmp_blackSidePile));
        }

        auto getPrivate() {
            return std::make_tuple(redStock, blackStock);
        }
        
        auto getDebugInfo() -> std::string {
            using json = nlohmann::json;
            json j{};

            j["redStock"] = redStock;
            j["blackStock"] = blackStock;
            j["redUpcard"] = redUpcard;
            j["blackUpcard"] = blackUpcard;
            j["redSidePile"] = redSidePile;
            j["blackSidePile"] = blackSidePile;

            return j.dump();
        }

    private:
        strVec redStock{};
        strVec blackStock{};
        strVec redUpcard{};
        strVec blackUpcard{};
        strVec redSidePile{};
        strVec blackSidePile{};
    };
}
