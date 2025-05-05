#include "stmts/LgsAssignment.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsSelection.h"
#include "stmts/LgsVarDec.h"
#include <LgsStack.h>

void LgsAssignment::createIRStmt(CodeGenMetadata* metadata) {
    if (const auto selection = lvalue->asSelection()) {
        selection->assignIRValue(metadata, rvalue);
        return;
    }
    if (const auto arrIndex = lvalue->asArrayIndex()) {
        arrIndex->assignIRValue(metadata, rvalue);
        return;
    }
    assert(false);
}

LgsAssignment::~LgsAssignment() {
    delete lvalue;
    delete rvalue;
}
