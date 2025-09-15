#include "external/doctest.h"
#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"

TEST_CASE("TestCodeGen1") {
    LgsApp app("./");
    app.appConfigs.logLevel = INFO;
    const auto code = R"(
    main() {
        print("Hello world")
    }
    )";
    app.loadBuiltins();
    app.parseSrcFile(code);
    app.analyse();
    app.generate();
    app.link();
    app.execute();
    // CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10000, code));
    // CHECK_EQ(app.errHandler.errors[0].errCode, E10000.errCode);
}