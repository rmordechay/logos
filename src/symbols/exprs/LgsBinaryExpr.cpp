#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

json::value LgsBinaryExpr::asJSON() {
    assert(0);
}

Value* LgsBinaryExpr::addIR(LgsCodeGen& codeGen, LgsExpr* other) {
    return left->addIR(codeGen, right);
}

Value* LgsBinaryExpr::subIR(LgsCodeGen& codeGen, LgsExpr* other) {
    return left->subIR(codeGen, right);
}

Value* LgsBinaryExpr::mulIR(LgsCodeGen& codeGen, LgsExpr* other) {
    return left->mulIR(codeGen, right);
}

Value* LgsBinaryExpr::divIR(LgsCodeGen& codeGen, LgsExpr* other) {
    return left->divIR(codeGen, right);
}

Value* LgsBinaryExpr::inIR(LgsCodeGen& codeGen, LgsExpr* other) {
    return left->inIR(codeGen, right);
}

Value* LgsBinaryExpr::modIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::eqIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::neIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::ltIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::gtIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::geIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::leIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::andIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::orIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitAndIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitOrIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitXorIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::rshiftIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::lshiftIR(LgsCodeGen& codeGen, LgsExpr* other)  {
    assert(0);
}

std::string LgsBinaryExpr::pname() {
    return left->pname() + ' ' + opStr + ' ' + right->pname();
}

LgsBinaryExpr::~LgsBinaryExpr() {
    if (left) {
        delete left;
        right = nullptr;
    }
    if (right) {
        delete right;
        left = nullptr;
    }
}
