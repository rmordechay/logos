#include "binary/LgsBinaryExpr.h"

#include "types/LgsInt.h"
#include "types/LgsStr.h"

Value* LgsBinaryExpr::createIRValue(CodeGenMetadata* metadata) {
    switch (op) {
    case ADD:
        return left->add(metadata, right);
    case SUB:
        return left->sub(metadata, right);
    case MUL:
        return left->mul(metadata, right);
    case DIV:
        return left->div(metadata, right);
    default:
        break;
    }
    const auto l = left->getIRValue(metadata);
    const auto r = right->getIRValue(metadata);
    auto& builder = metadata->builder;
    switch (op) {
    case NE:
        return builder.CreateICmpNE(l, r);
    case EQ:
        return builder.CreateICmpEQ(l, r);
    case LT:
        return builder.CreateICmpSLT(l, r);
    case GT:
        return builder.CreateICmpSGT(l, r);
    case GE:
        return builder.CreateICmpSGE(l, r);
    case LE:
        return builder.CreateICmpSLE(l, r);
    case NOOP:
        break;
    default:
        break;
    }
    return nullptr;
}
