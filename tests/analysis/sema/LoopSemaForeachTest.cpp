#include "LgsLinker.h"
#include "Logos.h"
#include "TestUtils.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class LoopSemaTests : public testing::Test {
protected:
    path dataDir = "../tests/analysis/sema";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltinFuncs();
    }

    void TearDown() override {
        remove_all(logos.buildDir);
    }
};

TEST_F(LoopSemaTests, TestSemaForeachLoopWorks) {
    const auto code = R"(
    main() {
        for i in [1, 2, 3, 4] {
            print(i)
        }
    }
    )";
    const auto file = logos.parseFile(code);
    logos.analyse({file});

    ASSERT_THAT(logos.errors.size(), 0);
}

TEST_F(LoopSemaTests, TestSemaNotIterable) {
    const auto code = R"(
    main() {
        arr = 4
        for i in arr {
            print(i)
        }
    }
    )";
    const auto file = logos.parseFile(code);
    logos.analyse({file});

    ASSERT_THAT(logos.errors.size(), 1);
    ASSERT_THAT(logos.errors[0].msg, StartsWith("Error: 'arr' is not iterable."));
    ASSERT_THAT(logos.errors[0].errCode, E10002.errCode);
}