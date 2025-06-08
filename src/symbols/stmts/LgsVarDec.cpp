#include "stmts/LgsVarDec.h"
#include "exprs/unary/LgsArrayExpr.h"


string LgsVarDec::format(string& indentStr) {
    return indentStr + name + " = ";
}

void LgsVarDec::createIRStmt(LgsRuntime* runtime) {
    const auto IRType = type->getIRType(runtime);
    const auto exprIRValue = expr->getIRValue(runtime);
    if (shouldAllocate(IRType)) {
        IRValue = runtime->builder.CreateAlloca(IRType);
        runtime->builder.CreateStore(exprIRValue, IRValue);
    } else {
        IRValue = exprIRValue;
    }
}

bool LgsVarDec::shouldAllocate(const Type* IRType) const {
    if (type->asMap() || type->asArray()) return false;
    return IRType->isArrayTy() || IRType->isPointerTy() || IRType->isVoidTy();
}

json LgsVarDec::asJSON() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->prettyName();
    tree["stmtType"] = "VAR_DEC";
    return tree;
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}
