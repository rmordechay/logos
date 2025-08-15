#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

void LgsBinaryExpr::createIRValue(LgsCodeGen* codeGen) {
    switch (op) {
    case ADD:
        IRValue = left->addIR(codeGen, right);
        break;
    case SUB:
        IRValue = left->subIR(codeGen, right);
        break;
    case MUL:
        IRValue = left->mulIR(codeGen, right);
        break;
    case DIV:
        IRValue = left->divIR(codeGen, right);
        break;
    case MOD:
        IRValue = left->modIR(codeGen, right);
        break;
    case EQ:
        IRValue = left->eqIR(codeGen, right);
        break;
    case NE:
        IRValue = left->neIR(codeGen, right);
        break;
    case AND:
        IRValue = left->andIR(codeGen, right);
        break;
    case OR:
        IRValue = left->orIR(codeGen, right);
        break;
    case LT:
        IRValue = left->ltIR(codeGen, right);
        break;
    case GT:
        IRValue = left->gtIR(codeGen, right);
        break;
    case GE:
        IRValue = left->geIR(codeGen, right);
        break;
    case LE:
        IRValue = left->leIR(codeGen, right);
        break;
    case BIT_AND:
        IRValue = left->bitAndIR(codeGen, right);
        break;
    case BIT_OR:
        IRValue = left->bitOrIR(codeGen, right);
        break;
    case BIT_XOR:
        IRValue = left->bitXorIR(codeGen, right);
        break;
    case LSHIFT:
        IRValue = left->rshiftIR(codeGen, right);
        break;
    case RSHIFT:
        IRValue = left->lshiftIR(codeGen, right);
        break;
    case NOOP:
        assert(0);
    }
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

std::string LgsBinaryExpr::prettyName() {
    return left->prettyName() + ' ' + opStr + ' ' + right->prettyName();
}