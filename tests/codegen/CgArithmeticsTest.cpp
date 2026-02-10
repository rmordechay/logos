#include "logos/LgsApp.h"
#include <cassert>
#include <sstream>
#include "gtest/gtest.h"
#include <unistd.h>

TEST(CgArithmeticsTest, IntTest1) {
    const auto code = R"(
    main() {
        a = 23 + 34 - 235
        print(a)
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
