#include "logos/LgsApp.h"
#include <cassert>
#include <sstream>
#include "gtest/gtest.h"
#include <unistd.h>

#include "LgsTestUtils.h"

TEST(CgDArrTest, Test1) {
    const auto code = R"(
    main() {
        arr = [1, 2]
        print(arr)
        arr.add(3)
        print(arr)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    std::string line1, line2;
    std::getline(stream, line1);
    std::getline(stream, line2);
    EXPECT_EQ(line1, "[1, 2]");
    EXPECT_EQ(line2, "[1, 2, 3]");
}
