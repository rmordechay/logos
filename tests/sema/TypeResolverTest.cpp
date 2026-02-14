#include "logos/LgsApp.h"
#include <string>

#include "exprs/LgsArrayExpr.h"
#include "gtest/gtest.h"
#include "files/LgsMainFile.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsNullable.h"
#include "types/iterables/LgsSArray.h"

TEST(TypeResolverTest, SArrStr) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2] = [5, 6]
        arr2: Str[2] = ["text1", "text"]
    })";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    app.analyse();
    const auto mainFunc = app.getMainFile()->funcs.at(LGS_MAIN_FUNC);

    const auto varDec1 = mainFunc->stmtsBlock->stmts[0].stmt->asVarDec();
    const auto sArr1 = varDec1->type->asSArray();
    const auto arr1 = varDec1->expr->asArrayExpr();
    ASSERT_TRUE(sArr1);
    ASSERT_TRUE(sArr1->baseType->asInt());
    ASSERT_TRUE(arr1->elements[0]->type->asInt());
    ASSERT_TRUE(arr1->elements[1]->type->asInt());
    ASSERT_TRUE(varDec1->expr->type == varDec1->type);

    const auto varDec2 = mainFunc->stmtsBlock->stmts[1].stmt->asVarDec();
    const auto sArr2 = varDec2->type->asSArray();
    const auto arr2 = varDec2->expr->asArrayExpr();
    ASSERT_TRUE(sArr2);
    ASSERT_TRUE(sArr2->baseType->asStr());
    ASSERT_TRUE(arr2->elements[0]->type->asStr());
    ASSERT_TRUE(arr2->elements[1]->type->asStr());
    ASSERT_TRUE(varDec2->expr->type == varDec2->type);
}
