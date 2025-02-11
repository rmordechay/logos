#include "stmts/LogosReturnStmt.h"

Value* LogosReturnStmt::getLLVMValue(CodeGenMetadata* metadata) {
    const auto exprLLVM = expr->getLLVMValue(metadata);
    return metadata->builder->CreateRet(exprLLVM);
}

LogosReturnStmt::~LogosReturnStmt() {
    delete expr;
}
