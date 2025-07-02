#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

string LgsBinaryExpr::prettyName() {
    return left->prettyName() + ' ' + opStr + ' ' + right->prettyName();
}

Value* LgsBinaryExpr::createIRValue(LgsModule* module) {
    switch (op) {
    case ADD:
        return left->addIR(module, right);
    case SUB:
        return left->subIR(module, right);
    case MUL:
        return left->mulIR(module, right);
    case DIV:
        return left->divIR(module, right);
    case MOD:
        return left->modIR(module, right);
    case EQ:
        return left->eqIR(module, right);
    case NE:
        return left->neIR(module, right);
    case AND:
        return left->andIR(module, right);
    case OR:
        return left->orIR(module, right);
    case LT:
        return left->ltIR(module, right);
    case GT:
        return left->gtIR(module, right);
    case GE:
        return left->geIR(module, right);
    case LE:
        return left->leIR(module, right);
    case BIT_AND:
        return left->bitAndIR(module, right);
    case BIT_OR:
        return left->bitOrIR(module, right);
    case BIT_XOR:
        return left->bitXorIR(module, right);
    case LSHIFT:
        return left->rshiftIR(module, right);
    case RSHIFT:
        return left->lshiftIR(module, right);
    case NOOP:
        break;
    }
    assert(0);
}

Value* LgsBinaryExpr::addIR(LgsModule* module, LgsExpr* other) {
    return left->addIR(module, right);
}

Value* LgsBinaryExpr::subIR(LgsModule* module, LgsExpr* other) {
    return left->subIR(module, right);
}

Value* LgsBinaryExpr::mulIR(LgsModule* module, LgsExpr* other) {
    return left->mulIR(module, right);
}

Value* LgsBinaryExpr::divIR(LgsModule* module, LgsExpr* other) {
    return left->divIR(module, right);
}
