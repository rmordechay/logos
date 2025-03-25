#include "LgsLinker.h"
#include "Logos.h"
#include "TestUtils.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaPatternMatchingTests : public testing::Test {
protected:
    path dataDir = "../tests/analysis/sema/pattern_matching/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltinFuncs();
    }

    void TearDown() override {
        remove_all(logos.buildDir);
    }
};

TEST_F(SemaPatternMatchingTests, TestTypeDoesNotMatch) {
    const auto code = R"(
    main() {
        a = "apple"
        if a {
            "apple": { print("apple") }
            3: { print("orange") }
            else:  { print("else") }
        }
    }
    )";
    const auto file = logos.parseFile(code);
    logos.analyse({file});

    ASSERT_THAT(logos.errors.size(), 1);
    ASSERT_THAT(logos.errors[0].msg, StartsWith("Error: Pattern of type 'Int' does not match base type 'Str'."));
    ASSERT_THAT(logos.errors[0].errCode, E10014.errCode);
}