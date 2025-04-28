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
    case NOOP:
        break;
    }
    return nullptr;
}

Value* LgsBinaryExpr::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    return compute(metadata)->addIR(metadata, other);
}

LgsExpr* LgsBinaryExpr::compute(CodeGenMetadata* metadata) {
    if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(left)) {
        results = unaryExpr->add(right);
        return results;
    }
    if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(left)) {
        return binaryExpr->compute(metadata);
    }
    return nullptr;
}

LgsBinaryExpr::~LgsBinaryExpr() {
    if (results) delete results;
}
