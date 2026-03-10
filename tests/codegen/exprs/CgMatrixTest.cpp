#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgMatrixTest, Test1) {
    const auto code = R"(
    main() {
        mat = Mat3x3(
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
            [7.0, 8.0, 9.0],
        )
        print(mat)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    //EXPECT_EQ(lines[0], "Mat3x3([1, 2, 3], [4, 5, 6], [7, 8, 9])");
}
