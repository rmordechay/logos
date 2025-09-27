#include "stmts/LgsVarDec.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsPtr.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/DIBuilder.h>

Value* LgsVarDec::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

void LgsVarDec::setDebugValue(LgsLLVMGen& cg) {
    const auto var = cg.diBuilder->createAutoVariable(
        cg.compileUnit,
        name,
        cg.diFile,
        location.lineStart,
        type->getDebugType(cg)
    );
    cg.diBuilder->insertDeclare(
        IRValue,
        var,
        cg.diBuilder->createExpression(),
        getDebugLoc(cg),
        cg.builder.GetInsertBlock()
    );
}

json::value LgsVarDec::asJsonStr() {
    json::object obj;
    obj["stmtKind"] = "VarDec";
    obj["type"] = type->asJsonStr();
    obj["expr"] = expr->asJsonStr();
    return obj;
}

LgsVarDec::~LgsVarDec() {
    if (expr) {
        freeExpr(expr);
        expr = nullptr;
    } else if (type) {
        freeType(type);
        type = nullptr;
    }
}
