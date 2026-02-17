#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgIoPairTest, Test1) {
    const auto code = R"(
    io(openFile, closeFile)
    openFile() {
        print("Opening file")
    }
    closeFile() {
        print("Closing file")
    }
    main() {
        io openFile() {
            print("Do Something")
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "Opening file");
    EXPECT_EQ(lines[1], "Do Something");
    EXPECT_EQ(lines[2], "Closing file");
}
