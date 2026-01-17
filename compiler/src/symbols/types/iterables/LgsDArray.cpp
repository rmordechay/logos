#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_Exprs.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto addFunc = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, baseType}, flags);
        addFunc->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            addIRElement(cg, args[0].expr, nullptr, args[1].expr);
            return nullptr;
        };
        addMethod(addFunc);
        return addFunc;
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
    return cg.getStructType({cg.i32Ty(), cg.ptrTy(), cg.sizeTy(), cg.sizeTy()}, name);
}

Constant* LgsDArray::getRTType(LgsCgModule& cg) {
    const auto dArrName = getName();
    const auto sv = cg.getRTTExtraStruct(dArrName, {cg.ptrTy()}, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(dArrName, sizeBytes(), RTT_DARRAY, sv, true);
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
    const auto alloc = pointee ? pointee : cg.heapAlloc(cg.usize(sizeBytes()));
    const auto initSize = cg.usize(LGS_MAP_INITIAL_CAPACITY * baseType->sizeBytes());
    cg.callLgsFunc(name, "initDArray", cg.voidTy(), {cg.ptrTy(), cg.sizeTy()}, {alloc, initSize});
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
        if (rightType->canCastTo(baseType)) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsDArray::lenIR(LgsCgModule& cg, Value* iterable) {
    const auto lenFieldPtr = getLenField(cg, iterable);
    return cg.load(cg.sizeTy(), lenFieldPtr);
}

Value* LgsDArray::inIR(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* value) {
    return cg.builder.CreateCall(generateContainsFunc(cg), {iterable->IRValue, value->IRValue});
}

Value* LgsDArray::getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) {
    const auto baseSize = cg.usize(baseType->sizeBytes());
    const auto dataFieldPtr = getDataField(cg, iterable->IRValue);
    const auto offset = cg.builder.CreateMul(cg.extendToSize(index->IRValue), baseSize);
    const auto dataField = cg.load(cg.ptrTy(), dataFieldPtr);
    auto ptr = cg.builder.CreateInBoundsPtrAdd(dataField, offset);
    if (baseType->passByRef) {
        ptr = cg.load(cg.ptrTy(), ptr);
    }
    return ptr;
}

void LgsDArray::addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) {
    if (index) assert(0);
    auto element = value->IRValue;
    if (baseType->isHeapAlloc) {
        element = cg.moveElement(iterable->IRValue, element, getRTType(cg));
    }
    cg.builder.CreateCall(generateAddFunc(cg), {iterable->IRValue, element});
}

Value* LgsDArray::getLevelField(LgsCgModule& cg, Value* iterable) {
    return cg.builder.CreateStructGEP(getIRType(cg), iterable, 0);
}

Value* LgsDArray::getDataField(LgsCgModule& cg, Value* iterable) {
    return cg.builder.CreateStructGEP(getIRType(cg), iterable, 1);
}

Value* LgsDArray::getLenField(LgsCgModule& cg, Value* iterable) {
    return cg.builder.CreateStructGEP(getIRType(cg), iterable, 2);
}

Value* LgsDArray::getCapField(LgsCgModule& cg, Value* iterable) {
    return cg.builder.CreateStructGEP(getIRType(cg), iterable, 3);
}

Function* LgsDArray::generateContainsFunc(LgsCgModule& cg) {
    const auto funcName = getName() + "_" + CONTAINS_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto valueTy = baseType->getTypeOrPtr(cg);
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), valueTy});
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
    cg.builder.SetInsertPoint(entryBlock);

    const auto arrIR = cg.currentFunc->getArg(0);
    const auto elementIR = cg.currentFunc->getArg(1);
    const auto tempArr = getZeroValue();
    const auto tempElement1 = baseType->getZeroValue();
    const auto tempElement2 = baseType->getZeroValue();
    tempArr->IRValue = arrIR;
    tempElement1->IRValue = elementIR;

    cg.loop(lenIR(cg, arrIR), [&](Value* iValue, BasicBlock*) {
        LgsIntConst size(&LGS_SIZE, 0);
        size.IRValue = iValue;
        const auto elementPtr = tempArr->type->asIterable()->getIRElement(cg, tempArr, &size);
        tempElement2->IRValue = cg.load(baseType->getIRType(cg), elementPtr);
        const auto elementsEqual = eqIR(cg, tempElement1, tempElement2);
        cg.ifStmt(elementsEqual, [&cg] {cg.builder.CreateRet(cg.true_());});
    });

    // Epilogue
    cg.builder.CreateRet(cg.false_());

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);

    freeExpr(tempArr);
    freeExpr(tempElement1);
    freeExpr(tempElement2);
    return func;
}

Function* LgsDArray::generateAddFunc(LgsCgModule& cg) {
    const auto funcName = getName() + "_" + ADD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto valueTy = baseType->getTypeOrPtr(cg);
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), valueTy});
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

    const auto ty = getIRType(cg);
    const auto arrIR = cg.currentFunc->getArg(0);
    const auto elementIR = cg.currentFunc->getArg(1);
    const auto dataGEP = getDataField(cg, arrIR);
    const auto lenGEP = getLenField(cg, arrIR);
    const auto capGEP = getCapField(cg, arrIR);

    auto len = cg.load(cg.sizeTy(), lenGEP);
    const auto cap = cg.load(cg.sizeTy(), capGEP);
    const auto needsResize = cg.builder.CreateICmpSGE(len, cap);
    cg.builder.CreateCondBr(needsResize, needsResizeBlock, exitBlock);

    // Resize
    cg.startBlock(needsResizeBlock);
    auto data = cg.load(cg.ptrTy(), dataGEP);
    const auto newCap = cg.builder.CreateMul(cap, cg.usize(2));
    const auto baseTypeSize = cg.usize(baseType->sizeBytes());
    const auto newSize = cg.builder.CreateMul(newCap, baseTypeSize);
    const auto level = cg.load(cg.i32Ty(), getLevelField(cg, arrIR));
    const auto newPtr = cg.reallocate(data, newSize, level);
    cg.store(newPtr, dataGEP);
    cg.storeStructField(ty, arrIR, 3, newCap);

    // Set element
    cg.branchAndStartBlock(exitBlock);
    len = cg.load(cg.sizeTy(), lenGEP);
    data = cg.load(cg.ptrTy(), dataGEP);
    const auto offset = cg.builder.CreateMul(len, baseTypeSize);
    const auto elementPtr = cg.builder.CreateInBoundsPtrAdd(data, offset);
    cg.store(elementIR, elementPtr);

    // Increment length
    const auto inc = cg.builder.CreateAdd(len, cg.usize(1));
    cg.storeStructField(ty, arrIR, 2, inc);

    // Epilogue
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
