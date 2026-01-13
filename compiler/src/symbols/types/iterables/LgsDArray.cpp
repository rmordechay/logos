#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_ArrayExpr.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>

#define INITIAL_CAPACITY 3

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, baseType}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            addIRElement(cg, args[0].expr, nullptr, args[1].expr);
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
        if (!arg->type->canCastTo(baseExprType)) return false;
    }
    baseType = baseExprType;
    if (const auto iter = baseType->asIterable()) {
        iter->isStatic = false;
    }
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
    return sizeof(Lgs_ArrayExpr);
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

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Value* LgsDArray::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto cap = cg.usize(INITIAL_CAPACITY);
    const auto initSize = cg.builder.CreateMul(cap, cg.usize(baseType->sizeBytes()));
    const auto alloc = pointee ? pointee : cg.heapAlloc(cg.usize(sizeBytes()));
    const auto entries = cg.heapAlloc(initSize);
    cg.storeStructField(ty, alloc, 0, entries);
    cg.storeStructField(ty, alloc, 1, cg.sizeZero());
    cg.storeStructField(ty, alloc, 2, cap);
    return alloc;
}

LgsType* LgsDArray::replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) {
    const auto otherDArr = replacement->asDArray();
    if (otherDArr) {
        baseType = baseType->replaceGenerics(otherDArr->baseType, replacements);
    } else {
        const auto baseName = baseType->getName();
        if (replacements.contains(baseName)) {
            baseType = replacements[baseName];
        }
    }
    return this;
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
    const std::vector<Value*> IRArgs = {iterableExpr->IRValue, getRTType(cg), value->IRValue};
    return cg.callLgsFunc(name, "contains", cg.i1Ty(), params, IRArgs);
}

Value* LgsDArray::getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) {
    const auto ty = getIRType(cg);
    const auto baseSize = cg.usize(baseType->sizeBytes());
    const auto dataFieldPtr = cg.builder.CreateStructGEP(ty, iterable->IRValue, 0);
    const auto offset = cg.builder.CreateMul(cg.extendToSize(index->IRValue), baseSize);
    const auto dataField = cg.load(cg.ptrTy(), dataFieldPtr);
    return cg.builder.CreateInBoundsPtrAdd(dataField, offset);
}

void LgsDArray::addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) {
    if (index) assert(0);
    cg.builder.CreateCall(generateAddFunc(cg), {iterable->IRValue, value->IRValue, nullptr});
}

Function* LgsDArray::generateAddFunc(LgsCgModule& cg) {
    const auto funcName = getName() + "_" + ADD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;

    const auto valueTy = baseType->getTypeOrPtr(cg);
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), valueTy, cg.sizeTy()});
    if (cg.mode == CG_MODE_SRC_CODE) {
        return cg.getFunc(funcName, ft);
    }

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    const auto func = cg.getFunc(funcName, ft);
    cg.currentFunc = func;

    // Prologue
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto needsResizeBlock = cg.createBlock("resize");
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto ty = getIRType(cg);
    const auto arrIR = cg.currentFunc->getArg(0);
    const auto elementIR = cg.currentFunc->getArg(1);
    const auto levelIR = cg.currentFunc->getArg(2);
    const auto dataGEP = cg.builder.CreateStructGEP(ty, arrIR, 0);
    const auto lenGEP = cg.builder.CreateStructGEP(ty, arrIR, 1);
    const auto capGEP = cg.builder.CreateStructGEP(ty, arrIR, 2);

    auto len = cg.load(cg.sizeTy(), lenGEP);
    const auto cap = cg.load(cg.sizeTy(), capGEP);
    const auto needsResize = cg.builder.CreateICmpSGE(len, cap);
    cg.builder.CreateCondBr(needsResize, needsResizeBlock, exitBlock);

    // Resize
    cg.startBlock(needsResizeBlock);
    auto data = cg.load(cg.ptrTy(), dataGEP);
    const auto newCap = cg.builder.CreateMul(cap, cg.usize(2));
    const auto newSize = cg.builder.CreateMul(newCap, cg.usize(baseType->sizeBytes()));
    const auto newPtr = cg.reallocate(data, newSize, levelIR);
    cg.store(newPtr, dataGEP);
    cg.storeStructField(ty, arrIR, 2, newCap);

    // Set element
    cg.branchAndStartBlock(exitBlock);
    len = cg.load(cg.sizeTy(), lenGEP);
    data = cg.load(cg.ptrTy(), dataGEP);
    const auto baseSize = cg.usize(baseType->sizeBytes());
    const auto offset = cg.builder.CreateMul(len, baseSize);
    const auto elementPtr = cg.builder.CreateInBoundsPtrAdd(data, offset);
    cg.store(elementIR, elementPtr);

    // Increment length
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.storeStructField(ty, arrIR, 1, inc);

    // Epilogue
    cg.callPopStack();
    cg.builder.CreateRetVoid();

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);

    return func;
}

std::string LgsDArray::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

DIType* LgsDArray::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsDArray::clone() {
    const auto newDArray = new LgsDArray(*this);
    newDArray->baseType = baseType->clone();
    return newDArray;
}
