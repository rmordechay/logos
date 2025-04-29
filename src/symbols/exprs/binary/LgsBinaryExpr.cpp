#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

Value* LgsBinaryExpr::createIRValue(CodeGenMetadata* metadata) {
    switch (op) {
    case ADD:
        return left->addIR(metadata, right);
    case SUB:
        return left->subIR(metadata, right);
    case MUL:
        return left->mulIR(metadata, right);
    case DIV:
        return left->divIR(metadata, right);
    case EQ:
        return left->eqIR(metadata, right);
    case NE:
        return left->neIR(metadata, right);
    case AND:
        return left->andIR(metadata, right);
    case OR:
        return left->orIR(metadata, right);
    case LT:
        return left->ltIR(metadata, right);
    case GT:
        return left->gtIR(metadata, right);
    case GE:
        return left->geIR(metadata, right);
    case LE:
        return left->leIR(metadata, right);
    case BIT_AND:
        return left->bitAndIR(metadata, right);
    case BIT_OR:
        return left->bitOrIR(metadata, right);
    case BIT_XOR:
        return left->bitXorIR(metadata, right);
    case LSHIFT:
        return left->rshiftIR(metadata, right);
    case RSHIFT:
        return left->lshiftIR(metadata, right);
    case NOOP:
        break;
    }
    return nullptr;
}

Value* LgsBinaryExpr::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto lIRValue = createIRValue(metadata);
    const auto rIRValue = other->createIRValue(metadata);
    return metadata->builder.CreateAdd(lIRValue, rIRValue);
}

Value* LgsBinaryExpr::subIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto lIRValue = createIRValue(metadata);
    const auto rIRValue = other->createIRValue(metadata);
    return metadata->builder.CreateSub(lIRValue, rIRValue);
}

Value* LgsBinaryExpr::mulIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto lIRValue = createIRValue(metadata);
    const auto rIRValue = other->createIRValue(metadata);
    return metadata->builder.CreateMul(lIRValue, rIRValue);
}

Value* LgsBinaryExpr::divIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto lIRValue = createIRValue(metadata);
    const auto rIRValue = other->createIRValue(metadata);
    return metadata->builder.CreateSDiv(lIRValue, rIRValue);
}
