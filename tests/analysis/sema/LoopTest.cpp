#include "LgsLinker.h"
#include "Logos.h"
#include <LogosParser.h>
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>

using testing::StartsWith;

const path dataDir = "../tests/analysis/sema";

TEST(SemaTest, TestNotIterable) {
    Logos logos(dataDir);
    const auto files = logos.parseFiles();
    map<string, LgsSymbol> globalSymbols;
    logos.loadGlobals(files);

    const ostringstream outputBuffer;
    const auto buffer = cout.rdbuf(outputBuffer.rdbuf());
    logos.analyse(files);
    cout.rdbuf(buffer);
    const auto output = outputBuffer.str();

    ASSERT_THAT(output, StartsWith("Error: 'arr' is not iterable"));
}
