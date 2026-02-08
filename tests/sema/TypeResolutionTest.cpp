#include "logos/LgsApp.h"
#include <string>

#include "exprs/LgsArrayExpr.h"
#include "gtest/gtest.h"
#include "files/LgsMainFile.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsNullable.h"
#include "types/iterables/LgsSArray.h"

TEST(TypeResolutionTest, SArrStr) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Str[2] = ["text1", "text"]
    }
    )";
    app.loadSrcFile(code);
    app.analyse();
    const auto mainFunc = app.getMainFile()->getMainFunc();
    const auto varDec = mainFunc->stmtsBlock->stmts.front().stmt->asVarDec();
    const auto sArr = varDec->type->asSArray();
    const auto arr = varDec->expr->asArrayExpr();
    ASSERT_TRUE(sArr);
    ASSERT_TRUE(sArr->baseType->asStr());
    ASSERT_TRUE(arr->elements[0]->type->asStr());
    ASSERT_TRUE(arr->elements[1]->type->asStr());
    ASSERT_TRUE(varDec->expr->type == varDec->type);
}

TEST(TypeResolutionTest, SArrStrNullable) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Str?[2] = ["text1", null]
    }
    )";
    app.loadSrcFile(code);
    app.analyse();
    const auto mainFunc = app.getMainFile()->getMainFunc();
    const auto varDec = mainFunc->stmtsBlock->stmts.front().stmt->asVarDec();
    const auto sArr = varDec->type->asSArray();
    const auto arr = varDec->expr->asArrayExpr();
    ASSERT_TRUE(sArr);
    const auto nullable = sArr->baseType->asNullable();
    ASSERT_TRUE(nullable);
    ASSERT_TRUE(nullable->baseType->asStr());
    ASSERT_TRUE(arr->elements[0]->type->asNullable());
    ASSERT_TRUE(arr->elements[1]->isNull && arr->elements[1]->type->asNullable());
    ASSERT_TRUE(varDec->expr->type == varDec->type);
}
