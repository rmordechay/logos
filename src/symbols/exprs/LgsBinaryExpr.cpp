#include "exprs/LgsBinaryExpr.h"

#include "utils/LgsUtils.h"

json::value LgsBinaryExpr::asJSON() {
    assert(0);
}

Value* LgsBinaryExpr::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    return left->addIR(cg, right);
}

Value* LgsBinaryExpr::subIR(LgsLLVMGen& cg, LgsExpr* other) {
    return left->subIR(cg, right);
}

Value* LgsBinaryExpr::mulIR(LgsLLVMGen& cg, LgsExpr* other) {
    return left->mulIR(cg, right);
}

Value* LgsBinaryExpr::divIR(LgsLLVMGen& cg, LgsExpr* other) {
    return left->divIR(cg, right);
}

Value* LgsBinaryExpr::inIR(LgsLLVMGen& cg, LgsExpr* other) {
    return left->inIR(cg, right);
}

Value* LgsBinaryExpr::modIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::eqIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::neIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::ltIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::gtIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::geIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::leIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::andIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::orIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitAndIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitOrIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::bitXorIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::rshiftIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

Value* LgsBinaryExpr::lshiftIR(LgsLLVMGen& cg, LgsExpr* other)  {
    assert(0);
}

std::string LgsBinaryExpr::pname() {
    return left->pname() + ' ' + opStr + ' ' + right->pname();
}

LgsBinaryExpr::~LgsBinaryExpr() {
    if (left) {
        freeExpr(left);
        right = nullptr;
    }
    if (right) {
        freeExpr(right);
        left = nullptr;
    }
}
