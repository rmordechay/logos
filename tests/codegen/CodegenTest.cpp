#include "logos/LgsApp.h"
#include <cassert>
#include <sstream>
#include "gtest/gtest.h"
#include <unistd.h>

TEST(TestCodeGen, Test1) {
    const auto code = R"(
    main() {
        print("Hello world")
    }
    )";
    fs::path execPath = "";
    {
        LgsApp app;
        app.lgsCode[LGS_MAIN_FILE] = code;
        ASSERT_TRUE(app.compile());
        execPath = app.paths.execFile;
    }
    const auto pipe = popen(execPath.c_str(), "r");
    assert(pipe);
    std::string output;
    char buffer[64];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    pclose(pipe);
    std::istringstream stream(output);
    std::string line1;
    std::getline(stream, line1);
    EXPECT_EQ(line1, "Hello world");
}

TEST(TestCodeGen, Test2) {
    const auto code = R"(
    main() {
        a = 23 + 34 - 235
        print(a)
    }
    )";
    fs::path execPath = "";
    {
        LgsApp app;
        app.lgsCode[LGS_MAIN_FILE] = code;
        ASSERT_TRUE(app.compile());
        execPath = app.paths.execFile;
    }
    const auto pipe = popen(execPath.c_str(), "r");
    assert(pipe);
    std::string output;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    pclose(pipe);
    std::istringstream stream(output);
    std::string line1;
    std::getline(stream, line1);
    EXPECT_EQ(line1, "-178");
}

TEST(TestCodeGen, Test3) {
    const auto code = R"(
    main() {
        a = 5
        if a > 5 {
            print(false)
        } else {
            print(true)
        }
        if a < 5 {
            print(true)
        } else {
            print(false)
        }
    }
    )";
    fs::path execPath = "";
    {
        LgsApp app;
        app.lgsCode[LGS_MAIN_FILE] = code;
        ASSERT_TRUE(app.compile());
        execPath = app.paths.execFile;
    }
    const auto pipe = popen(execPath.c_str(), "r");
    assert(pipe);
    std::string output;
    char buffer[64];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    pclose(pipe);
    std::istringstream stream(output);
    std::string line1, line2;
    std::getline(stream, line1);
    std::getline(stream, line2);
    EXPECT_EQ(line1, "true");
    EXPECT_EQ(line2, "false");
}

TEST(TestCodeGen, Test4) {
    const auto code = R"(
    main() {
        arr: Str?[2] = ["text1", null]
        print(arr)
    }
    )";
    fs::path execPath = "";
    {
        LgsApp app;
        app.lgsCode[LGS_MAIN_FILE] = code;
        ASSERT_TRUE(app.compile());
        execPath = app.paths.execFile;
    }
    const auto pipe = popen(execPath.c_str(), "r");
    assert(pipe);
    std::string output;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    pclose(pipe);
    std::istringstream stream(output);
    std::string line1;
    std::getline(stream, line1);
    EXPECT_EQ(line1, "[text1, null]");
}
