#include "exprs/LgsVectorExpr.h"

Value* LgsVectorExpr::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(vecType->getIRType(cg), IRValue);
}

Value* LgsVectorExpr::addIR(LgsLLVMGen& cg, Value* other) {
    if (other->getType()->isIntegerTy()) {
        return cg.builder.CreateAdd(loadIR(cg), other);
    }
    return cg.builder.CreateFAdd(loadIR(cg), other);
}

Value* LgsVectorExpr::subIR(LgsLLVMGen& cg, Value* other) {
    if (other->getType()->isIntegerTy()) {
        return cg.builder.CreateSub(loadIR(cg), other);
    }
    return cg.builder.CreateFSub(loadIR(cg), other);
}

Value* LgsVectorExpr::mulIR(LgsLLVMGen& cg, Value* other) {
    auto loadOther = other;
    const auto loadThis = loadIR(cg);
    if (other->getType()->isIntegerTy()) {
        const auto vecTy = cast<VectorType>(loadThis->getType());
        loadOther = cg.builder.CreateSIToFP(loadOther, vecTy->getElementType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFMul(loadThis, loadOther);
    }
    if (other->getType()->isVectorTy()) {
        return dotProduct(cg, loadThis, loadOther);
    }
    if (other->getType()->isFloatingPointTy()) {
        const auto vecTy = cast<VectorType>(loadThis->getType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFMul(loadThis, loadOther);
    }
    return cg.builder.CreateFMul(loadThis, loadOther);
}

Value* LgsVectorExpr::divIR(LgsLLVMGen& cg, Value* other) {
    return LgsExpr::divIR(cg, other);
}

Value* LgsVectorExpr::dotProduct(LgsLLVMGen& cg, Value* lVec, Value* rVec) const {
    const auto vecTypeIR = lVec->getType();
    const auto vectorDim = vecType->vectorDim;

    cg.savedIP = cg.builder.saveIP();
    const auto dotFunc = cg.getFunc("Lgs_dotProduct", cg.getFT(cg.sizeTy(), {vecTypeIR, vecTypeIR}));
    const auto block = cg.createBlock("entry", dotFunc);
    cg.builder.SetInsertPoint(block);
    const auto l = dotFunc->getArg(0);
    const auto r = dotFunc->getArg(1);

    const auto lx = cg.builder.CreateExtractValue(l, {0});
    const auto rx = cg.builder.CreateExtractValue(r, {0});
    const auto ly = cg.builder.CreateExtractValue(l, {1});
    const auto ry = cg.builder.CreateExtractValue(r, {1});
    const auto mulX = cg.builder.CreateFMul(lx, rx);
    const auto mulY = cg.builder.CreateFMul(ly, ry);
    Value* result = cg.builder.CreateFAdd(mulX, mulY);
    if (vectorDim == 3) {
        const auto lz = cg.builder.CreateExtractValue(l, {2});
        const auto rz = cg.builder.CreateExtractValue(r, {2});
        const auto mulZ = cg.builder.CreateFMul(lz, rz);
        result = cg.builder.CreateFAdd(result, mulZ);
    } else if (vectorDim == 4) {
        const auto lw = cg.builder.CreateExtractValue(l, {3});
        const auto rw = cg.builder.CreateExtractValue(r, {3});
        const auto mulW = cg.builder.CreateFMul(lw, rw);
        result = cg.builder.CreateFAdd(result, mulW);
    }
    cg.builder.CreateRet(result);
    cg.builder.restoreIP(cg.savedIP);

    return cg.builder.CreateCall(dotFunc, {lVec, rVec});
}

std::string LgsVectorExpr::getName() {
    return vecType->pname();
}

auto LgsVectorExpr::asJsonStr() -> json::value {
    json::object obj;
    return obj;
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : args) {
        delete arg;
    }
    args.clear();
}
