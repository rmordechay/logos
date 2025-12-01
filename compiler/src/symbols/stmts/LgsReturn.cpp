#include "stmts/LgsReturn.h"

#include "codegen/LgsCgModule.h"
#include "funcs/LgsFunc.h"

void LgsReturn::setDebugValue(LgsCgModule& cg) {
    setDebugLoc(cg);
}

LgsReturn::~LgsReturn() {
    freeExpr(expr);
    expr = nullptr;
}
