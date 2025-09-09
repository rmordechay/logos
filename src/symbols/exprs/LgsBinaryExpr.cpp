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
    return left->modIR(cg, right);
}

Value* LgsBinaryExpr::eqIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->eqIR(cg, right);
}

Value* LgsBinaryExpr::neIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->neIR(cg, right);
}

Value* LgsBinaryExpr::ltIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->ltIR(cg, right);
}

Value* LgsBinaryExpr::gtIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->gtIR(cg, right);
}

Value* LgsBinaryExpr::geIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->geIR(cg, right);
}

Value* LgsBinaryExpr::leIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->leIR(cg, right);
}

Value* LgsBinaryExpr::andIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->andIR(cg, right);
}

Value* LgsBinaryExpr::orIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->orIR(cg, right);
}

Value* LgsBinaryExpr::bitAndIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->bitAndIR(cg, right);
}

Value* LgsBinaryExpr::bitOrIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->bitOrIR(cg, right);
}

Value* LgsBinaryExpr::bitXorIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->bitXorIR(cg, right);
}

Value* LgsBinaryExpr::rshiftIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->rshiftIR(cg, right);
}

Value* LgsBinaryExpr::lshiftIR(LgsLLVMGen& cg, LgsExpr* other)  {
    return left->lshiftIR(cg, right);
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
