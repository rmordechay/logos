#include "LgsLinker.h"
#include "Logos.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class LoopCodegenTests : public testing::Test {
protected:
    path dataDir = "../tests/codegen/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltinFuncs();
    }

    void TearDown() override {
        remove_all(logos.buildDir);
    }
};

TEST_F(LoopCodegenTests, TestCodegenForeachLoopWorks) {
    const auto code = R"(
    main() {
        for i in [1, 2, 3, 4] {
            print(i)
        }
    }
    )";
    const auto file = logos.parseFile(code);
    const auto files = {file};
    logos.analyse(files);
    logos.generateCode(logos.getMainFile(files));

    ASSERT_THAT(modules.size(), 1);
}
