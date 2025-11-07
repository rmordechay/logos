#include "logos/LgsApp.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include "external/doctest.h"

TEST_CASE("TestCodeGen1") {
    const auto code = R"(
    main() {
        print("Hello world")
    }
    )";
    fs::path execPath = "";
    {
        LgsApp app;
        app.lgsCode[LGS_MAIN_FILE] = code;
        app.compile();
        execPath = app.appPaths.execFile;
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
    CHECK(line1 == "Hello world");
}

TEST_CASE("TestCodeGen2") {
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
        app.compile();
        execPath = app.appPaths.execFile;
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
    CHECK(line1 == "-178");
}

TEST_CASE("TestCodeGen3") {
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
        app.compile();
        execPath = app.appPaths.execFile;
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
    CHECK(line1 == "true");
    CHECK(line2 == "false");
}
