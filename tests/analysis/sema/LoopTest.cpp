#include "Logos.h"
#include <LogosParser.h>
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

const string dataDir = "../tests/analysis/sema/data/";

TEST(SemaTest, TestNotIterable) {
    Logos logos(dataDir);
    const auto files = logos.parseFiles();
    map<string, LgsSymbol> globalSymbols;
    logos.addGlobalsSymbols(files, globalSymbols);

    ostringstream outputBuffer;
    auto buffer = cout.rdbuf(outputBuffer.rdbuf());
    logos.analyse(files, globalSymbols);
    cout.rdbuf(buffer);
    auto output = outputBuffer.str();

    EXPECT_THAT(output, StartsWith("Error: 'arr' is not iterable"));
}
