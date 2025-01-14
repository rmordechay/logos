#include "StoreExpr.h"
#include "RuntimeScope.h"
#include "exprs/LogosBinaryExpr.h"

#include <iostream>


Value* StoreExpr::getUnary(LogosUnaryExpr* unary) const {
    const auto llvmType = unary->type.getLLVMType(*builder);
    if (const auto constExpr = dynamic_cast<LogosConstantExpr*>(unary)) {
        if (const auto intValue = get_if<int>(&constExpr->value)) {
            return ConstantInt::get(llvmType, *intValue);
        }
    }
    return nullptr;
}

Value* StoreExpr::getBinary(const LogosBinaryExpr* binary) {
    const auto l = getExpr(binary->left);
    const auto r = getExpr(binary->right);
    if (binary->op == PLUS) {
        return builder->CreateAdd(l, r);
    }
    return nullptr;
}

Value* StoreExpr::getExpr(LogosExpr* expr) {
    if (const auto unary = dynamic_cast<LogosUnaryExpr*>(expr)) {
        return getUnary(unary);
    }
    if (const auto binary = dynamic_cast<LogosBinaryExpr*>(expr)) {
        return getBinary(binary);
    }
    return nullptr;
}

void StoreExpr::generateProlog(RuntimeScope* scope) {
    const auto value = getExpr(expr);
    const auto allocaInst = builder->CreateAlloca(value->getType());
    builder->CreateStore(value, allocaInst);
    scope->symbols[name] = allocaInst;
}

void StoreExpr::generateEpilog(RuntimeScope* scope) {
}
