#include "exprs/LgsVectorExpr.h"

Value* LgsVectorExpr::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(vecType->getIRType(cg), IRValue);
}

Value* LgsVectorExpr::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto loadLeft = loadIR(cg);
    const auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        return cg.builder.CreateAdd(loadLeft, loadRight);
    }
    return cg.builder.CreateFAdd(loadLeft, loadRight);
}

Value* LgsVectorExpr::subIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto loadLeft = loadIR(cg);
    const auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        return cg.builder.CreateSub(loadLeft, loadRight);
    }
    return cg.builder.CreateFSub(loadLeft, loadRight);
}

Value* LgsVectorExpr::mulIR(LgsLLVMGen& cg, LgsExpr* other) {
    const auto loadLeft  = loadIR(cg);
    auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        const auto vecTy = cast<VectorType>(loadLeft->getType());
        loadRight = cg.builder.CreateSIToFP(loadRight, vecTy->getElementType());
        loadRight = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadRight);
        return cg.builder.CreateFMul(loadLeft, loadRight);
    }
    if (other->type->asFloat()) {
        const auto vecTy = cast<VectorType>(loadLeft->getType());
        loadRight = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadRight);
        return cg.builder.CreateFMul(loadLeft, loadRight);
    }
    return cg.builder.CreateFMul(loadLeft, loadRight);
}

Value* LgsVectorExpr::divIR(LgsLLVMGen& cg, LgsExpr* other) {
    assert(0);
}

std::string LgsVectorExpr::pname() {
    return vecType->pname();
}

auto LgsVectorExpr::asJSON() -> json::value {
    json::object obj;
    return obj;
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : args) {
        delete arg;
    }
    args.clear();
}
