#include "logos/LgsApp.h"
#include <cassert>
#include <sstream>
#include "gtest/gtest.h"
#include <unistd.h>

TEST(CgIfStmtTest, Test1) {
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
        app.lgsCode = code;
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