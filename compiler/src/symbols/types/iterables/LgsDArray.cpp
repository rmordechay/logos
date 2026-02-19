#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_Exprs.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsArrayExpr.h"
#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>
#include "LgsRTTIndices.h"
#include "exprs/LgsFuncCall.h"

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(methodName)) return methods[methodName];
        const auto addFunc = new LgsFunc(methodName, name, &LGS_VOID, {this, baseType}, flags);
        addFunc->fn = [this](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto iterable = args[0].expr->IRValue;
            const auto value = args[1].expr->IRValue;
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
    const auto otherArr = other->asIterable();
    if (!otherArr) return false;
    if (!baseType || !otherArr->baseType) return false;
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

bool LgsDArray::hasGenerics() {
    return getNestedBaseType()->hasGenerics();
}

void LgsDArray::replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements) {
    const auto nestedTypeName = getNestedBaseType()->getName();
    if (replacements.contains(nestedTypeName) && replacements[nestedTypeName]) {
        setNestedBaseType(replacements[nestedTypeName]);
        return;
    }
    const auto genericName = getName();
    if (replacements.contains(genericName) && replacements[genericName]) {
        const auto otherNestedBaseType = replacements[genericName]->asIterable()->getNestedBaseType();
        replacements[nestedTypeName] = otherNestedBaseType;
        setNestedBaseType(otherNestedBaseType);
    }
}

Constant* LgsDArray::getRTTypeExtra(LgsCodeGen& cg) {
    return baseType->getRTType(cg);
}

Value* LgsDArray::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.callRuntimeFunc("allocDArr", cg.ptrTy(), {cg.ptrTy()}, {baseType->getRTType(cg)});
}

Value* LgsDArray::lenIR(LgsCodeGen& cg, Value* iterable) {
    const auto lenFieldPtr = cg.builder.CreateStructGEP(getIRType(cg), iterable, LgsDArrExprIndices::length);
    return cg.loadSize(lenFieldPtr);
}

Value* LgsDArray::inIR(LgsCodeGen& cg, Value* iterable, Value* value) {
    return cg.builder.CreateCall(getContainsFunc(cg), {iterable, value});
}

Value* LgsDArray::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    const auto baseSize = baseType->IRSize(cg);
    const auto dataFieldPtr = cg.builder.CreateStructGEP(getIRType(cg), iterable, LgsDArrExprIndices::data);
    const auto offset = cg.builder.CreateMul(cg.toSize(index), baseSize);
    const auto dataField = cg.loadPtr(dataFieldPtr);
    return cg.builder.CreateInBoundsPtrAdd(dataField, offset);
}

void LgsDArray::addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) {
    assert(!index);
    if (baseType->isHeap) {
        value = cg.moveValue(baseType->getBaseName(), value, cg.getLevel(iterable));
    }
    cg.builder.CreateCall(getAddFunc(cg), {iterable, value});
}

void LgsDArray::asIRText(LgsStrBuilder& sb, Value* ptr) {
    auto& cg = sb.cg;
    const auto data = loadRTData(cg, ptr);
    const auto len = loadRTLength(cg, ptr);
    sb.add("[");
    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto isFirst = cg.builder.CreateICmpNE(iValue, cg.zeroSize());
        cg.ifStmt(isFirst, [&] {sb.add(", ");});
        const auto offset = cg.builder.CreateMul(iValue, baseType->IRSize(cg));
        auto element = cg.builder.CreatePtrAdd(data, offset);
        element = cg.load(baseType->getIRType(cg), element);
        baseType->asIRText(sb, element);
    });
    sb.add("]");
}

Value* LgsDArray::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.callHash(getRTType(cg), value);
}

Function* LgsDArray::getAddFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + name + baseType->getBaseName() + "_" + ADD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), baseType->getStorageType(cg)});
    if (cg.mode == CG_MODE_SRC) return cg.getFunc(funcName, ft);

    // Prologue
    cg.savedIP = cg.builder.saveIP();
    const auto func = cg.getFunc(funcName, ft);
    const auto needsResizeBlock = cg.createBlock("resize");
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);
    cg.startFunc(func);

    const auto ty = getIRType(cg);
    const auto arrIR = func->getArg(0);
    const auto elementIR = func->getArg(1);
    const auto dataGEP = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::data);
    const auto lenGEP = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::length);
    const auto capGEP = cg.builder.CreateStructGEP(ty, arrIR, LgsDArrExprIndices::capacity);

    auto len = cg.loadSize(lenGEP);
    const auto cap = cg.loadSize(capGEP);
    const auto needsResize = cg.builder.CreateICmpSGE(len, cap);
    cg.builder.CreateCondBr(needsResize, needsResizeBlock, exitBlock);

    // Resize
    cg.startBlock(needsResizeBlock);
    auto data = cg.loadPtr(dataGEP);
    const auto newCap = cg.builder.CreateMul(cap, cg.usize(2));
    const auto baseTypeSize = baseType->IRSize(cg);
    const auto newSize = cg.builder.CreateMul(newCap, baseTypeSize);
    const auto level = cg.getLevel(arrIR);
    const auto newPtr = cg.reallocate(data, newSize, level);
    cg.store(newPtr, dataGEP);
    cg.storeField(ty, arrIR, LgsDArrExprIndices::capacity, newCap);

    // Set element
    cg.branchAndStartBlock(exitBlock);
    len = cg.loadSize(lenGEP);
    data = cg.loadPtr(dataGEP);
    const auto offset = cg.builder.CreateMul(len, baseTypeSize);
    const auto elementPtr = cg.builder.CreateInBoundsPtrAdd(data, offset);
    cg.store(elementIR, elementPtr);

    // Increment length
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.storeField(ty, arrIR, LgsDArrExprIndices::length, inc);

    cg.builder.CreateRetVoid();
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Function* LgsDArray::getContainsFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + name + baseType->getBaseName() + "_" + CONTAINS_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), baseType->getStorageType(cg)});
    if (cg.mode == CG_MODE_SRC) return cg.getFunc(funcName, ft);

    // Prologue
    const auto func = cg.getFunc(funcName, ft);
    cg.startFunc(func);
    const auto arrIR = func->getArg(0);
    const auto value = func->getArg(1);

    cg.loop(lenIR(cg, arrIR), [&](Value* iValue, BasicBlock*) {
        LgsIntConst size(&LGS_SIZE, 0);
        size.IRValue = iValue;
        const auto elementPtr = getIRElement(cg, arrIR, size.IRValue);
        const auto element = cg.load(baseType->getStorageType(cg), elementPtr);
        const auto elementsAreEqual = eqIR(cg, value, element, baseType);
        cg.ifStmt(elementsAreEqual, [&cg] {cg.builder.CreateRet(cg.true_());});
    });

    cg.builder.CreateRet(cg.false_());
    return func;
}

Function* LgsDArray::getEqFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + name + baseType->getBaseName() + "_" + EQUAL_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC) return cg.getFunc(funcName, ft);
    const auto func = cg.getFunc(funcName, ft);

    cg.savedIP = cg.builder.saveIP();
    cg.startFunc(func);
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

Value* LgsDArray::loadRTBaseType(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(getRTTStruct(cg), ptr, LgsDArrExprIndices::baseType, cg.ptrTy());
}

Value* LgsDArray::loadRTLength(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(getRTTStruct(cg), ptr, LgsDArrExprIndices::length, cg.sizeTy());
}

Value* LgsDArray::loadRTCapacity(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(getRTTStruct(cg), ptr, LgsDArrExprIndices::capacity, cg.sizeTy());
}

Value* LgsDArray::loadRTData(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(getRTTStruct(cg), ptr, LgsDArrExprIndices::data, cg.ptrTy());
}

StructType* LgsDArray::getRTTStruct(LgsCodeGen& cg) {
    return cg.getStructType({cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.sizeTy(), cg.sizeTy()}, name);
}