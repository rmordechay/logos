#include "stmts/LgsReturn.h"

#include "codegen/LgsCgModule.h"
#include "funcs/LgsFunc.h"

void LgsReturn::setDebugValue(LgsCgModule& cg) {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
