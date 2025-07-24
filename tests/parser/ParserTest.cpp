#include "logos/LgsApp.h"
#include <doctest.h>

TEST_CASE("TestParser") {
    LgsApp app;
    app.parseSrcFile("main() {a: Str = 34}");
    CHECK(app.errHandler.errors.empty());
}