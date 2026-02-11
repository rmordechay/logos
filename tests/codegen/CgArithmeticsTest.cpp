#include "logos/LgsApp.h"
#include <cassert>
#include <sstream>
#include "gtest/gtest.h"
#include <unistd.h>

#include "LgsTestUtils.h"

TEST(CgArithmeticsTest, IntTest1) {
    const auto code = R"(
    main() {
        print(23 + 34)
        print(23 - 235)
        print(23 * 34)
        print(23 + 34 - 235)
        print(23 - 34 * 2)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    std::string line1, line2, line3, line4, line5;
    std::getline(stream, line1);
    std::getline(stream, line2);
    std::getline(stream, line3);
    std::getline(stream, line4);
    std::getline(stream, line5);
    EXPECT_EQ(line1, "57");
    EXPECT_EQ(line2, "-212");
    EXPECT_EQ(line3, "782");
    EXPECT_EQ(line4, "-178");
    EXPECT_EQ(line5, "-45");
}
