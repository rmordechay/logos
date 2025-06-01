#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

Value* LgsBinaryExpr::createIRValue(CodegenMetadata* metadata) {
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

Value* LgsBinaryExpr::addIR(CodegenMetadata* metadata, LgsExpr* other) {
    return left->addIR(metadata, right);
}

Value* LgsBinaryExpr::subIR(CodegenMetadata* metadata, LgsExpr* other) {
    return left->subIR(metadata, right);
}

Value* LgsBinaryExpr::mulIR(CodegenMetadata* metadata, LgsExpr* other) {
    return left->mulIR(metadata, right);
}

Value* LgsBinaryExpr::divIR(CodegenMetadata* metadata, LgsExpr* other) {
    return left->divIR(metadata, right);
}
