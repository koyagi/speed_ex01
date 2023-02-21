#include "../dealer.hpp"
#include <gtest/gtest.h>

#include <set>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CreateInitialTableFixture : public ::testing::Test {
    protected:
    GameTable table{};
    virtual void SetUp() {
        const auto initialStatus = R"({"blackSidePile":[],"blackStock":["SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK","CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK"],"blackUpcard":[],"redSidePile":[],"redStock":["DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK","HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK"],"redUpcard":[]})"s;
        table = GameTable(initialStatus);
    }
};


TEST_F(CreateInitialTableFixture, test_initial_status) {
    auto initialStatus = R"({"blackSidePile":[],"blackStock":["SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK","CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK"],"blackUpcard":[],"redSidePile":[],"redStock":["DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK","HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK"],"redUpcard":[]})"s;
    EXPECT_EQ(table.getDebugInfo(), initialStatus);
}

TEST_F(CreateInitialTableFixture, test_turnup_r1) {
    auto expected = strSet{};
    auto redUpcard = strSet{};

    table.turnup(GameTable::Player::RED);
    expected = std::set{"HK"s};
    redUpcard = json::parse(table.getDebugInfo()).at("redUpcard").get<std::set<std::string>>();
    EXPECT_EQ(redUpcard, expected);
    
    table.turnup(GameTable::Player::RED);
    redUpcard = json::parse(table.getDebugInfo()).at("redUpcard").get<std::set<std::string>>();
    expected = std::set{"HK"s, "HQ"s};
    EXPECT_EQ(redUpcard, expected);
    
    table.turnup(GameTable::Player::RED);
    redUpcard = json::parse(table.getDebugInfo()).at("redUpcard").get<std::set<std::string>>();
    expected = std::set{"HK"s, "HQ"s, "HJ"s};
    EXPECT_EQ(redUpcard, expected);
    
    table.turnup(GameTable::Player::RED);
    redUpcard = json::parse(table.getDebugInfo()).at("redUpcard").get<std::set<std::string>>();
    expected = std::set{"HK"s, "HQ"s, "HJ"s, "H10"s};
    EXPECT_EQ(redUpcard, expected);
    
    table.turnup(GameTable::Player::RED);
    redUpcard = json::parse(table.getDebugInfo()).at("redUpcard").get<std::set<std::string>>();
    EXPECT_EQ(redUpcard, expected);
    expected = std::set{"HK"s, "HQ"s, "HJ"s, "H10"s, "H9"s};
    EXPECT_NE(redUpcard, expected);
}

TEST_F(CreateInitialTableFixture, test_turnup_b1) {
    auto expected = strSet{};
    auto blackUpcard = strSet{};

    table.turnup(GameTable::Player::BLACK);
    expected = std::set{"CK"s};
    blackUpcard = json::parse(table.getDebugInfo()).at("blackUpcard").get<std::set<std::string>>();
    EXPECT_EQ(blackUpcard, expected);
    
    table.turnup(GameTable::Player::BLACK);
    blackUpcard = json::parse(table.getDebugInfo()).at("blackUpcard").get<std::set<std::string>>();
    expected = std::set{"CK"s, "CQ"s};
    EXPECT_EQ(blackUpcard, expected);
    
    table.turnup(GameTable::Player::BLACK);
    blackUpcard = json::parse(table.getDebugInfo()).at("blackUpcard").get<std::set<std::string>>();
    expected = std::set{"CK"s, "CQ"s, "CJ"s};
    EXPECT_EQ(blackUpcard, expected);
    
    table.turnup(GameTable::Player::BLACK);
    blackUpcard = json::parse(table.getDebugInfo()).at("blackUpcard").get<std::set<std::string>>();
    expected = std::set{"CK"s, "CQ"s, "CJ"s, "C10"s};
    EXPECT_EQ(blackUpcard, expected);
    
    table.turnup(GameTable::Player::BLACK);
    blackUpcard = json::parse(table.getDebugInfo()).at("blackUpcard").get<std::set<std::string>>();
    EXPECT_EQ(blackUpcard, expected);
    expected = std::set{"CK"s, "CQ"s, "CJ"s, "C10"s, "C9"s};
    EXPECT_NE(blackUpcard, expected);
}