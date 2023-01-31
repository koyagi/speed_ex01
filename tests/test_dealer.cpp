#include "gtest/gtest.h"
#include "../dealer.hpp"

#include <set>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class CreateDecksFixture : public ::testing::Test {
    protected:
    std::vector<std::string> expected_red_deck{ "DA"s, "D2"s, "D3"s, "D4"s, "D5"s, "D6"s, "D7"s, "D8"s, "D9"s, "D10"s, "DJ"s, "DQ"s, "DK"s, "HA"s, "H2"s, "H3"s, "H4"s, "H5"s, "H6"s, "H7"s, "H8"s, "H9"s, "H10"s, "HJ"s, "HQ"s, "HK"s };
    std::vector<std::string> expected_black_deck{ "SA"s, "S2"s, "S3"s, "S4"s, "S5"s, "S6"s, "S7"s, "S8"s, "S9"s, "S10"s, "SJ"s, "SQ"s, "SK"s, "CA"s, "C2"s, "C3"s, "C4"s, "C5"s, "C6"s, "C7"s, "C8"s, "C9"s, "C10"s, "CJ"s, "CQ"s, "CK"s };
    std::set<std::string> expected_set_red{};
    std::set<std::string> expected_set_black{};
    virtual void SetUp() {
        expected_set_red = createDataSetAs<std::set<std::string>>( expected_red_deck );
        expected_set_black = createDataSetAs<std::set<std::string>>( expected_black_deck );
    }
};

// Compile will fail on this code when create_half_deck() is not aware universal-refarence.
TEST_F(CreateDecksFixture, createHalfDeck_isUniversalReference) {
        // R-value argument test
        auto deck_red = create_half_deck({ "D"s, "H"s });
        EXPECT_EQ(deck_red, expected_red_deck);

        // L-value argument test
        const auto suits_black = std::vector<std::string>{ "S"s, "C"s };
        auto deck_black = create_half_deck(suits_black);
        EXPECT_EQ(deck_black, expected_black_deck);
}

TEST_F(CreateDecksFixture, createDecks_cardIndexCheck) {
    auto [stock_red, stock_black] = create_akakuro_decks();
    auto stock_set_red = createDataSetAs<std::set<std::string>>(stock_red);
    auto stock_set_black = createDataSetAs<std::set<std::string>>(stock_black);
    EXPECT_EQ(stock_set_red, expected_set_red);
    EXPECT_EQ(stock_set_black, expected_set_black);
}

TEST_F(CreateDecksFixture, createDecks_mayBeRandom) {
    auto [stock_red, stock_black] = create_akakuro_decks();
    EXPECT_NE(stock_red, expected_red_deck);
    EXPECT_NE(stock_black, expected_black_deck);
}

TEST_F(CreateDecksFixture, table_constructor_test01) {
    EXPECT_NO_THROW(
        auto table = GameTable{};
    );
}

TEST_F(CreateDecksFixture, table_constructor_test02) {
    auto table = GameTable{};
    auto [stock_red, stock_black] = table.getPrivate();
    EXPECT_NE(stock_red, expected_red_deck);
    EXPECT_NE(stock_black, expected_black_deck);
}

// template<typename T> class TD; 

TEST_F(CreateDecksFixture, getDebugInfo) {
    using json = nlohmann::json;

    auto table = GameTable{};
    auto j = json::parse( table.getDebugInfo() );

    auto stock_red = j["redStock"];
    auto stock_set_red = createDataSetAs<std::set<std::string>>(stock_red);
    EXPECT_EQ(stock_set_red, expected_set_red);

    auto stock_black = j["blackStock"];
    auto stock_set_black = createDataSetAs<std::set<std::string>>(stock_black);
    EXPECT_EQ(stock_set_black, expected_set_black);

    EXPECT_EQ(j["redUpcard"].size(), 0);
    EXPECT_EQ(j["blackUpcard"].size(), 0);
    EXPECT_EQ(j["redSidePile"].size(), 0);
    EXPECT_EQ(j["blackSidePile"].size(), 0);
}