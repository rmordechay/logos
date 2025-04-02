#include "LgsLinker.h"
#include "Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaEnumsTests : public testing::Test {
protected:
    path dataDir = "../tests/analysis/sema/enums/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltins();
    }

    void TearDown() override {
        remove_all(logos.buildDir);
    }
};

TEST_F(SemaEnumsTests, TestEnumsWorks) {
    const auto code = R"(
    enum MyEnum {
        A = "value A"
        B = "value A"
    }

    main() {

    }
    )";
    const auto file = logos.parseFile(code);
    logos.analyse({file});
}