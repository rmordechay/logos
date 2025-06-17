#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

string LgsBinaryExpr::prettyName() {
    return left->prettyName() + ' ' + opStr + ' ' + right->prettyName();
}

Value* LgsBinaryExpr::createIRValue(LgsRuntime* runtime) {
    switch (op) {
    case ADD:
        return left->addIR(runtime, right);
    case SUB:
        return left->subIR(runtime, right);
    case MUL:
        return left->mulIR(runtime, right);
    case DIV:
        return left->divIR(runtime, right);
    case MOD:
        return left->modIR(runtime, right);
    case EQ:
        return left->eqIR(runtime, right);
    case NE:
        return left->neIR(runtime, right);
    case AND:
        return left->andIR(runtime, right);
    case OR:
        return left->orIR(runtime, right);
    case LT:
        return left->ltIR(runtime, right);
    case GT:
        return left->gtIR(runtime, right);
    case GE:
        return left->geIR(runtime, right);
    case LE:
        return left->leIR(runtime, right);
    case BIT_AND:
        return left->bitAndIR(runtime, right);
    case BIT_OR:
        return left->bitOrIR(runtime, right);
    case BIT_XOR:
        return left->bitXorIR(runtime, right);
    case LSHIFT:
        return left->rshiftIR(runtime, right);
    case RSHIFT:
        return left->lshiftIR(runtime, right);
    case NOOP:
        break;
    }
    assert(0);
}

Value* LgsBinaryExpr::addIR(LgsRuntime* runtime, LgsExpr* other) {
    return left->addIR(runtime, right);
}

Value* LgsBinaryExpr::subIR(LgsRuntime* runtime, LgsExpr* other) {
    return left->subIR(runtime, right);
}

Value* LgsBinaryExpr::mulIR(LgsRuntime* runtime, LgsExpr* other) {
    return left->mulIR(runtime, right);
}

Value* LgsBinaryExpr::divIR(LgsRuntime* runtime, LgsExpr* other) {
    return left->divIR(runtime, right);
}
