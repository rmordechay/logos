#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsUnaryExpr.h"

json::value LgsBinaryExpr::asJSON() {
    assert(0);
}

Value* LgsBinaryExpr::addIR(LgsLLVM& codeGen, LgsExpr* other) {
    return left->addIR(codeGen, right);
}

Value* LgsBinaryExpr::subIR(LgsLLVM& codeGen, LgsExpr* other) {
    return left->subIR(codeGen, right);
}

Value* LgsBinaryExpr::mulIR(LgsLLVM& codeGen, LgsExpr* other) {
    return left->mulIR(codeGen, right);
}

Value* LgsBinaryExpr::divIR(LgsLLVM& codeGen, LgsExpr* other) {
    return left->divIR(codeGen, right);
}

Value* LgsBinaryExpr::inIR(LgsLLVM& codeGen, LgsExpr* other) {
    return left->inIR(codeGen, right);
}

Value* LgsBinaryExpr::modIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::eqIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::neIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::ltIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::gtIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::geIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::leIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::andIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::orIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitAndIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitOrIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitXorIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::rshiftIR(LgsLLVM& codeGen, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::lshiftIR(LgsLLVM& codeGen, LgsExpr* other)  {
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
