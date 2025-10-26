#include "external/doctest.h"
#include "logos/LgsApp.h"

#include <iostream>

TEST_CASE("TestCodeGen1") {
    const auto code = R"(
    main() {
        print("Hello world")
    }
    )";
    fs::path execPath = "";
    {
        LgsApp app;
        lgsConfigs.debug = false;
        lgsConfigs.writeIRFiles = false;
        app.lgsCode[LGS_MAIN_FILE] = code;
        assert(app.setup());
        app.compile();
        execPath = app.paths.execFilePath;
    }
    assert(execPath != "");
    const auto pipe = popen(execPath.c_str(), "r");
    if (!pipe) assert(0);
    char buffer[512];
    fgets(buffer, sizeof(buffer), pipe);
    std::string output(buffer);
    if (!output.empty() && output.back() == '\n') output.pop_back();
    CHECK(output == "Hello world");
}

TEST_CASE("TestCodeGen2") {
    // LgsApp app("./");
    // app.appConfigs.logLevel = INFO;
    // const auto code = R"(
    // main() {
    //     print(_/4 + _/4)
    // }
    // )";
    // app.loadBuiltins();
    // app.parseSrcFile(code);
    // app.analyse();
    // app.generate();
    // app.link();
    // app.execute();
}