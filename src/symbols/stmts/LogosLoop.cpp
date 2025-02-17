#include "stmts/LogosLoop.h"

#include <exprs/LogosExpr.h>
#include <stmts/LogosStmtBlock.h>

Value* LogosLoop::computeIRValue(CodeGenMetadata* metadata) {
    auto irValue = iterable->getIRValue(metadata);
    return nullptr;
}
