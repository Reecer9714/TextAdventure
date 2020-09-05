#include "GTest/gtest.h"

#include <interaction/Action.h>

using namespace ::testing;

class ActionPerformer_Test : public Test {
    public:
        ActionPerformer* af = af->getInstance();

        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(ActionPerformer_Test, perform_QuitActionSuccess_ErrorCode) {
    GameState state;

    ErrorCode ec = af->perform(Quit, state);

    EXPECT_EQ(ec, SUCCESS);

    EXPECT_EQ(state.running, false);
}