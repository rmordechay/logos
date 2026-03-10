#include <sstream>
#include <string>
#include <vector>

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

TEST(CgIoPairTest, Test2) {
    const auto code = R"(
    io(openFile, closeFile)
    openFile() {
        print("Opening file")
    }
    closeFile() {
        print("Closing file")
    }
    func() {
        io openFile() {
            print("Do Something")
        }
        print("After closing file")
    }
    main() {
        func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 4);
    EXPECT_EQ(lines[0], "Opening file");
    EXPECT_EQ(lines[1], "Do Something");
    EXPECT_EQ(lines[2], "Closing file");
    EXPECT_EQ(lines[3], "After closing file");
}

TEST(CgIoPairTest, Test3) {
    const auto code = R"(
    io(openFile, closeFile)
    openFile() {
        print("Opening file")
    }
    closeFile() {
        print("Closing file")
    }
    func() {
        io openFile() {
            print("Do Something")
            if true {
                return
            }
        }
        print("After closing file")
    }
    main() {
        func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "Opening file");
    EXPECT_EQ(lines[1], "Do Something");
    EXPECT_EQ(lines[2], "Closing file");
}

TEST(CgIoPairTest, Test4) {
    const auto code = R"(
    io(openFile, closeFile)
    openFile() {
        print("Opening file")
    }
    closeFile() {
        print("Closing file")
    }
    func() {
        io openFile() {
            if true {
                return
            }
            print("Do Something")
        }
        print("After closing file")
    }
    main() {
        func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Opening file");
    EXPECT_EQ(lines[1], "Closing file");
}
