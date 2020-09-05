// AllTests.cpp
#include "GTest/gtest.h"
#include "GTest/gmock.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}