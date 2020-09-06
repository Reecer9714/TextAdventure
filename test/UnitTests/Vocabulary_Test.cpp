#include "GTest/gtest.h"

#include <interaction/Vocabulary.h>

using namespace ::testing;

class Vocabulary_Test : public Test {
public:
    Vocabulary* vocab;

    void SetUp() override {
        vocab = new Vocabulary();
        vocab->AddWord("quit", Quit);
    }

    void TearDown() override {
        delete vocab;
        vocab = nullptr;
    }
};

TEST_F(Vocabulary_Test, AddVerb_DuplicateWord_ErrorCode){
    ErrorCode ec;

    ec = vocab->AddWord("quit", Quit);

    EXPECT_EQ(ec, DUPLICATE_WORD);
}

TEST_F(Vocabulary_Test, AddVerb_Success_ErrorCode){
    ErrorCode ec;
    Verb verb;

    ec = vocab->AddWord("newword", Quit);

    EXPECT_EQ(ec, SUCCESS);

    ec = vocab->GetVerb("newword", verb);

    EXPECT_EQ(ec, SUCCESS);

    EXPECT_EQ(verb, Quit);
}

TEST_F(Vocabulary_Test, GetVerb_FailedMatchVerb_ErrorCode){
    Verb verb;
    ErrorCode ec;

    ec = vocab->GetVerb("nomatch", verb);

    EXPECT_EQ(ec, FAILED_MATCH_VERB);
}

TEST_F(Vocabulary_Test, GetVerb_Success_ErrorCode){
    Verb verb;
    ErrorCode ec;

    ec = vocab->GetVerb("quit", verb);

    EXPECT_EQ(ec, SUCCESS);

    EXPECT_EQ(verb, Quit);
}