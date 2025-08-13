#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

string LgsBinaryExpr::prettyName() {
    return left->prettyName() + ' ' + opStr + ' ' + right->prettyName();
}

Value* LgsBinaryExpr::createIRValue(LgsCodeGen* codeGen) {
    switch (op) {
    case ADD:
        return left->addIR(codeGen, right);
    case SUB:
        return left->subIR(codeGen, right);
    case MUL:
        return left->mulIR(codeGen, right);
    case DIV:
        return left->divIR(codeGen, right);
    case MOD:
        return left->modIR(codeGen, right);
    case EQ:
        return left->eqIR(codeGen, right);
    case NE:
        return left->neIR(codeGen, right);
    case AND:
        return left->andIR(codeGen, right);
    case OR:
        return left->orIR(codeGen, right);
    case LT:
        return left->ltIR(codeGen, right);
    case GT:
        return left->gtIR(codeGen, right);
    case GE:
        return left->geIR(codeGen, right);
    case LE:
        return left->leIR(codeGen, right);
    case BIT_AND:
        return left->bitAndIR(codeGen, right);
    case BIT_OR:
        return left->bitOrIR(codeGen, right);
    case BIT_XOR:
        return left->bitXorIR(codeGen, right);
    case LSHIFT:
        return left->rshiftIR(codeGen, right);
    case RSHIFT:
        return left->lshiftIR(codeGen, right);
    case NOOP:
        break;
    }
    assert(0);
}

Value* LgsBinaryExpr::addIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return left->addIR(codeGen, right);
}

Value* LgsBinaryExpr::subIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return left->subIR(codeGen, right);
}

Value* LgsBinaryExpr::mulIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return left->mulIR(codeGen, right);
}

Value* LgsBinaryExpr::divIR(LgsCodeGen* codeGen, LgsExpr* other) {
    return left->divIR(codeGen, right);
}

Value* LgsBinaryExpr::modIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::eqIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::neIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::ltIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::gtIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::geIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::leIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::andIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::orIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitAndIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitOrIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitXorIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::rshiftIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::lshiftIR(LgsCodeGen* codeGen, LgsExpr* other)  {
    assert(0);
}
