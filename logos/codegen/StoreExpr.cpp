#include "StoreExpr.h"

#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosUnaryExpr.h"


void StoreExpr::generateCode(IRBuilder<>& builder, Module* module, std::map<std::string, Function*> functions) {
    if (const auto unary = dynamic_cast<LogosUnaryExpr*>(expr)) {

    } else if (const auto binary = dynamic_cast<LogosBinaryExpr*>(expr)) {
        if (binary->op == PLUS) {
            const auto vl = binary->left->exprType->getLLVMValue(builder);
            const auto vr = binary->right->exprType->getLLVMValue(builder);
            const auto ptr = builder.CreateAlloca(binary->exprType->getLLVMType(builder), nullptr, name);
            const auto value = builder.CreateAdd(vl, vr);
            builder.CreateStore(value, ptr);
        }
    }
}

