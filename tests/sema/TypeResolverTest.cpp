#include <string>
#include <filesystem>
#include <map>
#include <vector>

#include "logos/LgsApp.h"
#include "LgsTestUtils.h"
#include "exprs/LgsArrayExpr.h"
#include "gtest/gtest.h"
#include "files/LgsMainFile.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsSArray.h"
#include "LgsDefinitions.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsStmt.h"
#include "stmts/LgsStmtsBlock.h"

TEST(TypeResolverTest, SArrStr) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2] = [5, 6]
        arr2: Str[2] = ["text1", "text"]
    })";
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
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

TEST(TypeResolverTest, Generics1) {
    LgsApp app;
    const auto code = R"(
    func<T>(arr: T[]): T[] {
        return arr
    }
    main() {
        arr = func([1, 2, 3])
    }
    )";
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    const auto mainFile = app.getMainFile();
}

TEST(TypeResolverTest, Generics2) {
    LgsApp app;
    const auto code = R"(
    func<T>(arr: T[]): T {
        return arr[0]
    }
    main() {
        arr = func([1, 2, 3])
    }
    )";
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    const auto mainFile = app.getMainFile();
}