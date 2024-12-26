#include <gtest/gtest.h>

TEST(ParserTest, Test1) {
    ASSERT_EQ(4, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
