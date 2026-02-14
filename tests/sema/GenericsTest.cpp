#include "logos/LgsApp.h"
#include <string>
#include "gtest/gtest.h"
#include "files/LgsMainFile.h"

TEST(GenericsTest, Test1) {
    LgsApp app;
    const auto code = R"(
    func<T>(arr: T[]): T[] {
        return arr
    }
    main() {
        arr = func([1, 2, 3])
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    app.analyse();
    const auto mainFile = app.getMainFile();
    const auto genericFunc = mainFile->symbolTable.genericsFuncs.at("u_func_DArrayInt");
    ASSERT_TRUE(genericFunc);
    const auto rt = genericFunc->funcType->rt->asDArray();
    const auto pt = genericFunc->funcType->params.front().type->asDArray();
    ASSERT_TRUE(rt && rt->baseType->isInt);
    ASSERT_TRUE(pt && pt->baseType->isInt);
}

TEST(GenericsTest, Test2) {
    LgsApp app;
    const auto code = R"(
    func<T>(arr: T[]): T {
        return arr[0]
    }
    main() {
        arr = func([1, 2, 3])
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    app.analyse();
    const auto mainFile = app.getMainFile();
    const auto genericFunc = mainFile->symbolTable.genericsFuncs.at("u_func_DArrayInt");
    ASSERT_TRUE(genericFunc);
    const auto rt = genericFunc->funcType->rt;
    const auto pt = genericFunc->funcType->params.front().type->asDArray();
    ASSERT_TRUE(rt && rt->isInt);
    ASSERT_TRUE(pt && pt->baseType->isInt);
}
