#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_DArrayExpr.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>

#define INITIAL_CAPACITY 10

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, baseType}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            addIRElement(cg, args[0].expr->IRValue, nullptr, args[1].expr->IRValue);
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    return LgsIterable::getMethod(methodName);
}

bool LgsDArray::inferBaseType(std::vector<LgsExpr*>& args) {
    if (baseType) return true;
    assert(!args.empty());
    const auto baseExprType = args.front()->type;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!baseExprType->equals(arg->type)) return false;
    }
    baseType = baseExprType;
    return true;
}

Type* LgsDArray::getIRType(LgsCgModule& cg) {
    return cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy()}, name);
}

Constant* LgsDArray::getRTType(LgsCgModule& cg) {
    const auto dArrName = getName();
    const auto sv = cg.getRTTExtraStruct(dArrName, {cg.ptrTy()}, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(dArrName, sizeBytes(), RTT_DARRAY, sv);
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
    return sizeof(Lgs_DArrayExpr);
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Value* LgsDArray::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto ptr = pointee ? pointee : cg.builder.CreateAlloca(ty);
    const auto cap = cg.usize(INITIAL_CAPACITY);
    const auto initSize = cg.builder.CreateMul(cap, cg.usize(baseType->sizeBytes()));
    cg.storeStructField(ty, ptr, 0, cg.heapAllocate(initSize, true));
    cg.storeStructField(ty, ptr, 1, cg.sizeZero());
    cg.storeStructField(ty, ptr, 2, cap);
    return ptr;
}

std::string LgsDArray::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsDArray::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case IN: {
        const auto otherIter = rightType->asIterable();
        if (!otherIter) return nullptr;
        if (otherIter->getDimension() - 1 == getDimension()) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsDArray::lenIR(LgsCgModule& cg, Value* iterable) {
    const auto lenFieldPtr = cg.builder.CreateStructGEP(getIRType(cg), iterable, 1);
    return cg.load(cg.sizeTy(), lenFieldPtr);
}

Value* LgsDArray::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {iterableExpr->IRValue, getRTType(cg), cg.getPtrTo(value->IRValue)};
    return cg.callLgsFunc(name, "contains", cg.i1Ty(), params, IRArgs);
}

Value* LgsDArray::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const auto ty = getIRType(cg);
    const auto baseSize = cg.usize(baseType->sizeBytes());
    const auto dataFieldPtr = cg.builder.CreateStructGEP(ty, iterable, 0);
    const auto offset = cg.builder.CreateMul(index, baseSize);
    const auto dataField = cg.load(cg.ptrTy(), dataFieldPtr);
    return cg.builder.CreateInBoundsPtrAdd(dataField, offset);
}

void LgsDArray::addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) {
    if (index) assert(0);

    const auto funcName = getName() + "_add";
    if (const auto f = cg.IRModule->getFunction(funcName)) {
        cg.builder.CreateCall(f, {iterable, value});
        return;
    }
    const auto ty = getIRType(cg);
    const auto baseSize = cg.usize(baseType->sizeBytes());

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    const std::vector<Type*> params = {cg.ptrTy(), baseType->getIRType(cg)};
    const auto ft = cg.getFT(cg.voidTy(), params);
    const auto func = cg.getFunc(funcName, ft);
    cg.currentFunc = func;

    // Prologue
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto needsResizeBlock = cg.createBlock(BLOCK_IF_TRUE);
    const auto exitBlock = cg.createBlock(BLOCK_IF_EXIT);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto iterParam = cg.currentFunc->getArg(0);
    const auto valueParam = cg.currentFunc->getArg(1);
    const auto dataFieldPtr = cg.builder.CreateStructGEP(ty, iterParam, 0);
    const auto lenFieldPtr = cg.builder.CreateStructGEP(ty, iterParam, 1);
    const auto capFieldPtr = cg.builder.CreateStructGEP(ty, iterParam, 2);
    const auto dataField = cg.load(cg.ptrTy(), dataFieldPtr);
    const auto lenField = cg.load(cg.sizeTy(), lenFieldPtr);
    const auto capField = cg.load(cg.sizeTy(), capFieldPtr);

    const auto needsResize = cg.builder.CreateICmpSGE(lenField, capField);
    cg.builder.CreateCondBr(needsResize, needsResizeBlock, exitBlock);

    // Resize
    cg.startBlock(needsResizeBlock);
    const auto newCap = cg.builder.CreateMul(capField, cg.usize(2));
    cg.storeStructField(ty, iterParam, 2, newCap);
    cg.reallocate(dataField, newCap, true);
    cg.branchAndStartBlock(exitBlock);

    // Set element
    const auto offset = cg.builder.CreateMul(lenField, baseSize);
    const auto elementPtr = cg.builder.CreateInBoundsPtrAdd(dataField, offset);
    cg.store(valueParam, elementPtr);

    // Increment length
    const auto inc = cg.builder.CreateAdd(lenField, cg.usize(1));
    cg.storeStructField(ty, iterParam, 1, inc);

    // Epilogue
    cg.callPopStack();
    cg.builder.CreateRetVoid();

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    cg.builder.CreateCall(func, {iterable, value});
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (other->asGenericType()) return true;
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

DIType* LgsDArray::getDebugType(LgsCgModule& cg) {
    assert(0);
}