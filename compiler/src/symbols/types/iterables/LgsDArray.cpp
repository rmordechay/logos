#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_Exprs.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsArrayExpr.h"
#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>

#include "LgsRTTIndices.h"

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(methodName)) return methods[methodName];
        const auto addFunc = new LgsFunc(methodName, name, &LGS_VOID, {this, baseType}, flags);
        addFunc->fn = [this](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto iterable = args[0].expr->IRValue;
            auto value = args[1].expr->IRValue;
            if (baseType->isHeap) {
                value = cg.moveArrElement(cg.load(cg.sizeTy(), iterable), baseType->getRTType(cg), value);
            }
            addIRElement(cg, iterable, nullptr, value);
            return nullptr;
        };
        addMethod(addFunc);
        return addFunc;
    }
    return LgsIterable::getMethod(methodName);
}

std::string LgsDArray::getBaseName() {
    return name;
}

std::string LgsDArray::getName() {
    return name + baseType->getName();
}

std::string LgsDArray::pname() {
    if (baseType) return baseType->pname() + "[]";
    return "[]";
}

size_t LgsDArray::sizeBytes() {
    return sizeof(Lgs_DArrExpr);
}

std::string LgsDArray::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (other->asGenericType()) return true;
    const auto otherArr = other->asIterable();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

LgsType* LgsDArray::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case EQ:
    case NE: {
        const auto otherDarr = rightType->asDArray();
        if (!otherDarr) return nullptr;
        if (otherDarr->baseType->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    case IN: {
        if (rightType->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Type* LgsDArray::getIRType(LgsCodeGen& cg) {
    return cg.getStructType({cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.sizeTy(), cg.sizeTy()}, name);
}

Constant* LgsDArray::getRTTypeExtra(LgsCodeGen& cg) {
    return baseType->getRTType(cg);
}

Value* LgsDArray::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.callRuntimeFunc("allocDArr", cg.ptrTy(), {cg.ptrTy()}, {baseType->getRTType(cg)});
}

Value* LgsDArray::lenIR(LgsCodeGen& cg, Value* iterable) {
    const auto lenFieldPtr = cg.builder.CreateStructGEP(getIRType(cg), iterable, LgsDArrExprIndices::len);
    return cg.load(cg.sizeTy(), lenFieldPtr);
}

Value* LgsDArray::inIR(LgsCodeGen& cg, Value* iterable, Value* value) {
    return cg.builder.CreateCall(getContainsFunc(cg), {iterable, value});
}

Value* LgsDArray::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    const auto baseSize = baseType->IRSize(cg);
    const auto dataFieldPtr = cg.builder.CreateStructGEP(getIRType(cg), iterable, LgsDArrExprIndices::data);
    const auto offset = cg.builder.CreateMul(cg.toSize(index), baseSize);
    const auto dataField = cg.loadPtr(dataFieldPtr);
    auto ptr = cg.builder.CreateInBoundsPtrAdd(dataField, offset);
    if (baseType->passByRef) {
        ptr = cg.loadPtr(ptr);
    }
    return ptr;
}

void LgsDArray::addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) {
    assert(!index);
    cg.builder.CreateCall(getAddFunc(cg), {iterable, value});
}

Value* LgsDArray::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.callHash(getRTType(cg), value);
}

Function* LgsDArray::getAddFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + name + baseType->getBaseName() + "_" + ADD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), baseType->getTypeOrPtr(cg)});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);

    // Prologue
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    const auto needsResizeBlock = cg.createBlock("resize");
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);
    cg.builder.SetInsertPoint(entryBlock);

    const auto ty = getIRType(cg);
    const auto arrIR = func->getArg(0);
    const auto elementIR = func->getArg(1);
    const auto dataGEP = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::data);
    const auto lenGEP = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::len);
    const auto capGEP = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::cap);

    auto len = cg.load(cg.sizeTy(), lenGEP);
    const auto cap = cg.load(cg.sizeTy(), capGEP);
    const auto needsResize = cg.builder.CreateICmpSGE(len, cap);
    cg.builder.CreateCondBr(needsResize, needsResizeBlock, exitBlock);

    // Resize
    cg.startBlock(needsResizeBlock);
    auto data = cg.loadPtr(dataGEP);
    const auto newCap = cg.builder.CreateMul(cap, cg.usize(2));
    const auto baseTypeSize = baseType->IRSize(cg);
    const auto newSize = cg.builder.CreateMul(newCap, baseTypeSize);
    const auto levelField = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::level);
    const auto level = cg.load(cg.i32Ty(), levelField);
    const auto newPtr = cg.reallocate(data, newSize, level);
    cg.store(newPtr, dataGEP);
    cg.storeStructField(ty, arrIR, LgsDArrExprIndices::cap, newCap);

    // Set element
    cg.branchAndStartBlock(exitBlock);
    len = cg.load(cg.sizeTy(), lenGEP);
    data = cg.loadPtr(dataGEP);
    const auto offset = cg.builder.CreateMul(len, baseTypeSize);
    const auto elementPtr = cg.builder.CreateInBoundsPtrAdd(data, offset);
    cg.store(elementIR, elementPtr);

    // Increment length
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.storeStructField(ty, arrIR, LgsDArrExprIndices::len, inc);

    cg.builder.CreateRetVoid();
    return func;
}

Function* LgsDArray::getContainsFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + name + baseType->getBaseName() + "_" + CONTAINS_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), baseType->getTypeOrPtr(cg)});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);

    // Prologue
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    const auto arrIR = func->getArg(0);
    const auto value = func->getArg(1);

    cg.loop(lenIR(cg, arrIR), [&](Value* iValue, BasicBlock*) {
        LgsIntConst size(&LGS_SIZE, 0);
        size.IRValue = iValue;
        const auto elementPtr = getIRElement(cg, arrIR, size.IRValue);
        const auto elementsAreEqual = eqIR(cg, value, cg.load(baseType->getTypeOrPtr(cg), elementPtr), baseType);
        cg.ifStmt(elementsAreEqual, [&cg] {cg.builder.CreateRet(cg.true_());});
    });

    cg.builder.CreateRet(cg.false_());
    return func;
}

Function* LgsDArray::getEqFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + name + baseType->getBaseName() + "_" + EQUAL_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);
    const auto func = cg.getFunc(funcName, ft);

    cg.savedIP = cg.builder.saveIP();
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    const auto ty = getIRType(cg);

    const auto arrIR1 = func->getArg(0);
    const auto arrIR2 = func->getArg(1);
    const auto len1 = lenIR(cg, arrIR1);
    const auto len2 = lenIR(cg, arrIR2);
    cg.ifStmt(cg.builder.CreateICmpNE(len1, len2), [&cg] {cg.builder.CreateRet(cg.false_());});
    const auto data1 = cg.builder.CreateStructGEP(ty, arrIR1, LgsDArrExprIndices::data);
    const auto data2 = cg.builder.CreateStructGEP(ty, arrIR2, LgsDArrExprIndices::data);
    const auto size = cg.builder.CreateMul(len1, baseType->IRSize(cg));

    cg.builder.CreateRet(cg.true_());
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

DIType* LgsDArray::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
