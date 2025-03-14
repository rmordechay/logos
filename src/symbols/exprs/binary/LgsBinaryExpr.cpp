#include "binary/LgsBinaryExpr.h"
#include "constants/LgsConst.h"

Value* LgsBinaryExpr::createIRValue(CodeGenMetadata* metadata) {
    const auto l = left->getIRValue(metadata);
    const auto r = right->getIRValue(metadata);
    auto& builder = metadata->builder;
    switch (op) {
    case ADD:
        return builder.CreateAdd(l, r);;
    case SUB:
        return builder.CreateSub(l, r);;
    case MUL:
        return builder.CreateMul(l, r);;
    case DIV:
        return builder.CreateSDiv(l, r);;
    case NE:
        return builder.CreateICmpNE(l, r);;
    case EQ:
        return builder.CreateICmpEQ(l, r);;
    case LT:
        return builder.CreateICmpSLT(l, r);;
    case GT:
        return builder.CreateICmpSGT(l, r);;
    case GE:
        return builder.CreateICmpSGE(l, r);;
    case LE:
        return builder.CreateICmpSLE(l, r);;
    case NOOP:
        break;
    }
    return nullptr;
}
