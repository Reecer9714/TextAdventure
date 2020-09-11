#include "GTest/gtest.h"

#include <interaction/ActionPerformer.h>

using namespace ::testing;

class ActionPerformer_Test : public Test {
    public:
        ActionPerformer* af;

        void SetUp() override {
            af = ActionPerformer::GetInstance();
        }

        void TearDown() override {
            delete af;
            af = nullptr;
        }
};

TEST_F(ActionPerformer_Test, perform_QuitActionSuccess_ErrorCode) {
    GameState state;

    ErrorCode ec = af->Perform(Verb::Quit, state);

    EXPECT_EQ(ec, SUCCESS);

    EXPECT_EQ(state.running, false);
}