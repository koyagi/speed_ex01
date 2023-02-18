#include "../dealer.hpp"
#include "gtest/gtest.h"

#include <set>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class CreateInitialTableFixture : public ::testing::Test {
    protected:
    GameTable table;
    virtual void SetUp() {
        auto initialStatus = R"({"blackSidePile":[],"blackStock":["SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK","CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK"],"blackUpcard":[],"redSidePile":[],"redStock":["DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK","HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK"],"redUpcard":[]})"s;
        table = GameTable{initialStatus};
    }
};


TEST_F(CreateInitialTableFixture, test_initial_status) {
    auto initialStatus = R"({"blackSidePile":[],"blackStock":["SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK","CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK"],"blackUpcard":[],"redSidePile":[],"redStock":["DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK","HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK"],"redUpcard":[]})"s;
    // auto table = GameTable{initialStatus};
    EXPECT_EQ(table.getDebugInfo(), initialStatus);
}