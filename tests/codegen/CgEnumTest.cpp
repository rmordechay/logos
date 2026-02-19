#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgEnumTest, Test1) {
    const auto code = R"(
    enum Enum {
        ENUM1
        ENUM2
        ENUM3
    }
    main() {
        e = Enum.ENUM1
        switch e {
            ENUM1: {print(e)}
            ENUM2: {print(e)}
            ENUM3: {print(e)}
            else: {print("else")}
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "ENUM1");
}
