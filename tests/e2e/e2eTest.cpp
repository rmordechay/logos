#include "LgsLinker.h"
#include "Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestUtils.h"


class E2ETests : public testing::Test {
protected:
    const path dataDir = "../tests/e2e/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        LgsFile* file = logos.parseFile("main() {print(\"Hello world\")}");
        logos.loadGlobals();
        logos.analyse({file});
        logos.generateCode(dynamic_cast<LgsMainFile*>(file));
        const LgsLinker linker(logos.objFilePath, logos.execFilePath);
        linker.link(modules);
    }

    void TearDown() override {
        logos.cleanup();
        remove_all(logos.buildDir);
    }
};

TEST_F(E2ETests, TestHelloWorld) {
    const auto output = executeAndGetOutput(logos.execFilePath.c_str());
    ASSERT_EQ(output, "Hello world\n");
}