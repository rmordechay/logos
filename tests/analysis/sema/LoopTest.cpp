#include "LgsLinker.h"
#include "Logos.h"
#include "TestUtils.h"

#include <LogosParser.h>
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;


class LoopTests : public testing::Test {
protected:
    path dataDir = "../tests/analysis/sema";
    Logos logos = Logos(dataDir);

    void TearDown() override {
        remove_all(logos.buildDir);
    }
};

TEST_F(LoopTests, TestNotIterable) {
    const auto code = R"(
    main() {
        arr = 4
        for i in arr {
            print(i)
        }
    }
    )";
    const auto file = logos.parseFile(code);
    logos.loadBuiltinFuncs();
    logos.analyse({file});

    ASSERT_THAT(logos.errors.size(), 1);
    ASSERT_THAT(logos.errors[0].msg, StartsWith("Error: 'arr' is not iterable."));
    ASSERT_THAT(logos.errors[0].errCode, E10002.errCode);
}