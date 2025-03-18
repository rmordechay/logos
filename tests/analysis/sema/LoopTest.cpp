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

    void SetUp() override {

    }

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
    logos.loadGlobals();

    const ostringstream outputBuffer;
    const auto buffer = cout.rdbuf(outputBuffer.rdbuf());
    logos.analyse({file});
    cout.rdbuf(buffer);
    const auto output = outputBuffer.str();

    ASSERT_THAT(output, StartsWith("Error: 'arr' is not iterable"));
}