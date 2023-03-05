#ifndef MY_DEALER_HPP
#define MY_DEALER_HPP

#include <algorithm>
#include <unordered_map>
#include <random>
// #include <set>
#include <unordered_set>
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
    // using strSet = std::set<std::string>;
    using strSet = std::unordered_set<std::string>;

    // template <typename T, typename S>
    // auto repackAs(const S & src) -> T {
    //     using std::begin;
    //     using std::end;
    //     return T(begin(src), end(src));
    // }
    template<typename T, typename S>
    auto repackAs(const S & org) -> decltype(auto) {
        static_assert(std::is_same<typename T::value_type, typename S::value_type>::value, "recreateDataSetAs(): Type mismach.");
        using std::begin;
        using std::end;
        return T(begin(org), end(org));
    }
    template<template<typename ...> typename TCont, typename S>    // type over-load to accept just container name for various containers.
    auto repackAs(const S & org) -> decltype(auto) {
        return repackAs<TCont<typename S::value_type>>(org);
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
            std::tie(stock[GameTable::Player::RED], stock[GameTable::Player::BLACK]) = create_akakuro_decks();
            upcard = {
                {GameTable::Player::RED, strSet{}},
                {GameTable::Player::BLACK, strSet{}}
            };
            pile = {
                {GameTable::Player::RED, strStack{}},
                {GameTable::Player::BLACK, strStack{}}
            };
        }

        GameTable(std::string debug_init) {
            using json = nlohmann::json;
            auto j = json::parse(debug_init);

            stock[GameTable::Player::RED] = strStack(j.at("redStock").get<strVec>());
            stock[GameTable::Player::BLACK] = strStack(j.at("blackStock").get<strVec>());
            upcard[GameTable::Player::RED] = repackAs<strSet>(j.at("redUpcard").get<strVec>());
            upcard[GameTable::Player::BLACK] = repackAs<strSet>(j.at("blackUpcard").get<strVec>());
            pile[GameTable::Player::RED] = strStack(j.at("redSidePile").get<strVec>());
            pile[GameTable::Player::BLACK] = strStack(j.at("blackSidePile").get<strVec>());
        }
        
        auto getDebugInfo() -> std::string {
            using json = nlohmann::json;
            json j{};

            j["redStock"] = stock.at(GameTable::Player::RED).getUnderlyingContainer();
            j["blackStock"] = stock.at(GameTable::Player::BLACK).getUnderlyingContainer();
            j["redUpcard"] = upcard.at(GameTable::Player::RED);
            j["blackUpcard"] = upcard.at(GameTable::Player::BLACK);
            j["redSidePile"] = pile.at(GameTable::Player::RED).getUnderlyingContainer();
            j["blackSidePile"] = pile.at(GameTable::Player::BLACK).getUnderlyingContainer();

            return j.dump();
        }

    void turnup(GameTable::Player pl) {
        if( upcard.at(pl).size() < 4 ) {
            upcard.at(pl).insert(stock.at(pl).safePop());
        }
    }

    private:
        std::unordered_map<GameTable::Player, strStack> stock{};
        std::unordered_map<GameTable::Player, strSet> upcard{};
        std::unordered_map<GameTable::Player, strStack> pile{};
    };
}

#endif