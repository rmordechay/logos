#include "types/iterables/LgsVec.h"
#include <llvm/IR/Module.h>
#include "LgsBinaryTokens.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/LgsAny.h"
#include "cblas/cblas.h"
#include "types/iterables/LgsMatrix.h"
#include <sstream>

LgsField* LgsVec::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    const size_t newFieldDim = fieldName.size();
    LgsField* field = nullptr;
    if (newFieldDim == 1) {
        field = new LgsField(fieldName, baseType);
        field->position = getComponentIndex(fieldName[0]);
    } else {
        field = new LgsField(fieldName, new LgsVec(newFieldDim));
    }
    addField(field);
    return field;
}

Type* LgsVec::getIRType(LgsCgModule& cg) {
    IRType = FixedVectorType::get(baseType->getIRType(cg), dimVec);
    return IRType;
}

Constant* LgsVec::getRTType(LgsCgModule& cg) {
    const auto name = getName();
    const auto sv = cg.getRTTExtraStruct(name, {cg.ptrTy()}, {baseType->getRTType(cg)});
    if (dimVec == 2) {
        return cg.getRTTypeInfo(name, sizeBytes(), RTT_VEC2, isHeapAlloc, sv);
    }
    if (dimVec == 3) {
        return cg.getRTTypeInfo(name, sizeBytes(), RTT_VEC3, isHeapAlloc, sv);
    }
    return cg.getRTTypeInfo(name, sizeBytes(), RTT_VEC4, isHeapAlloc, sv);
}

std::string LgsVec::getName() {
    return baseName + std::to_string(dimVec);
}

size_t LgsVec::sizeBytes() {
    return baseType->sizeBytes() * 2;
}

bool LgsVec::equals(LgsType* other) {
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    if (dimVec != otherVec->dimVec) return false;
    if (!baseType->equals(other)) return false;
    return true;
}

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr(this);
}

bool LgsVec::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    return dimVec == otherVec->dimVec && baseType->canCastTo(otherVec->baseType);
}

LgsType* LgsVec::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    const auto thisName = getName();
    const auto otherName = rightType->getName();
    switch (op.opType) {
    case ADD:
    case SUB:
    case DIV:
    case MODULO: {
        if (thisName == otherName || rightType->isNumber()) return this;
        break;
    }
    case CROSS: {
        if (dimVec == 3 && thisName == otherName) return this;
        break;
    }
    case MUL: {
        if (thisName == otherName) return &LGS_FLOAT; // dot product
        if (rightType->isNumber()) return this;
        break;
    }
    case IN: {
        if (rightType->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

bool LgsVec::inferBaseType(std::vector<LgsExpr*>& args) {
    if (args.empty()) return true;
    const auto firstArg = args.front();
    if (!firstArg->type) return false;
    const auto argsBaseType = firstArg->type->isNumber() ? firstArg->type : firstArg->type->asIterable()->baseType;
    if (!argsBaseType) return false;
    for (size_t i = 0; i < args.size(); ++i) {
        auto& arg = args[i];
        const auto type = arg->type->isNumber() ? arg->type : arg->type->asIterable()->baseType;
        if (!type->canCastTo(argsBaseType)) return false;
        castExprImplicitly(arg, argsBaseType);
    }
    baseType = argsBaseType;
    return true;
}

Value* LgsVec::getIRVector(LgsCgModule& cg, Value* value) {
    Value* result = UndefValue::get(getIRType(cg));
    for (size_t i = 0; i < dimVec; ++i) {
        result = cg.builder.CreateInsertElement(result, value, i);
    }
    return result;
}

Value* LgsVec::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (!baseType->isFloat) assert(0);
    auto [l, r] = loadPairAsFloat(cg, left, right);
    if (right->type->isNumber()) {
        r = getIRVector(cg, r);
    }
    return cg.builder.CreateFAdd(l, r);
}

Value* LgsVec::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (!baseType->isFloat) assert(0);
    auto [l, r] = loadPairAsFloat(cg, left, right);
    if (right->type->isNumber()) {
        r = getIRVector(cg, r);
    }
    return cg.builder.CreateFSub(l, r);
}

Value* LgsVec::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->asMatrix() && right->type->asVec()) {
        return matVecMul(cg, left, right);
    }
    if (!baseType->isFloat) assert(0);
    auto [l, r] = loadPairAsFloat(cg, left, right);
    if (right->type->isNumber()) {
        r = getIRVector(cg, r);
    }
    return cg.builder.CreateFMul(l, r);
}

Value* LgsVec::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (!baseType->isFloat) assert(0);
    auto [l, r] = loadPairAsFloat(cg, left, right);
    if (right->type->isNumber()) {
        r = getIRVector(cg, r);
    }
    return cg.builder.CreateFDiv(l, r);
}

Value* LgsVec::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (!baseType->isFloat) assert(0);
    auto [l, r] = loadPairAsFloat(cg, left, right);
    if (right->type->isNumber()) {
        r = getIRVector(cg, r);
    }
    return cg.builder.CreateFRem(l, r);
}

Value* LgsVec::crossIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto crossFunc = crossProductFunc(cg, left, right);
    return cg.builder.CreateCall(crossFunc, {left->loadIR(cg), right->loadIR(cg)});
}

Value* LgsVec::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.i1Ty());
    cg.store(cg.false_(), resultPtr);
    cg.loop(cg.i64(dimVec), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto tempExpr = iterableExpr->type->asIterable()->baseType->getZeroValue();
        tempExpr->IRValue = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = eqIR(cg, tempExpr, value);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.store(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
        freeExpr(tempExpr);
    });
    return cg.builder.CreateLoad(cg.i1Ty(), resultPtr);
}

Value* LgsVec::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.usize(dimVec);
}

Value* LgsVec::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    Value* vec = iterable;
    if (iterable->getType()->isPointerTy()) {
        vec = cg.builder.CreateLoad(getIRType(cg), iterable);
    }
    return cg.builder.CreateExtractElement(vec, index);
}

void LgsVec::addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    cg.store(value, gep);
}

Value* LgsVec::matVecMul(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) const {
    const auto mat = left->type->asMatrix();
    const auto order = cg.i32(CblasRowMajor);
    const auto transpose = cg.i32(CblasNoTrans);
    const auto m = cg.i32(mat->rows);
    const auto n = cg.i32(mat->columns);
    const auto alpha = cg.floatv(1);
    const auto matrixPtr = left->IRValue;
    const auto lda = cg.i32(mat->columns);
    const auto vectorPtr = cg.getPtrTo(right->IRValue);
    const auto incx = cg.i32(1);
    const auto beta = cg.floatv(0);
    const auto vecType = VectorType::get(baseType->getIRType(cg), mat->rows, false);
    const auto results = cg.builder.CreateAlloca(vecType);
    const auto incy = cg.i32(1);
    const std::vector<Type*> params = {
        cg.i32Ty(),     // order
        cg.i32Ty(),     // transpose
        cg.i32Ty(),     // m
        cg.i32Ty(),     // n
        cg.floatTy(),   // alpha
        cg.ptrTy(),     // matrixPtr
        cg.i32Ty(),     // lda
        cg.ptrTy(),     // vectorPtr
        cg.i32Ty(),     // incx
        cg.floatTy(),   // beta
        cg.ptrTy(),     // results
        cg.i32Ty()      // incy
    };
    const auto ft = cg.getFT(cg.voidTy(), params);
    const std::vector<Value*> args = {
        order, transpose, m, n, alpha, matrixPtr, lda, vectorPtr, incx, beta, results, incy
    };
    cg.builder.CreateCall(cg.getFunc("cblas_sgemv", ft), args);
    return results;
}

size_t LgsVec::getSwizzleSet(const char c) {
    if (strchr("xyzw", c)) return 0;
    if (strchr("rgba", c)) return 1;
    if (strchr("stpq", c)) return 2;
    return -1;
}

size_t LgsVec::getComponentIndex(const char c) {
    switch (c) {
    case 'x': case 'r': case 's': return 0;
    case 'y': case 'g': case 't': return 1;
    case 'z': case 'b': case 'p': return 2;
    case 'w': case 'a': case 'q': return 3;
    default: return -1;
    }
}

std::string LgsVec::fmtStr() const {
    std::stringstream str;
    str << '<';
    for (size_t i = 0; i < dimVec; i++) {
        str << baseType->fmtStr();
        if (i < dimVec - 1) str << ", ";
    }
    str << '>';
    return str.str();
}

DIType* LgsVec::getDebugType(LgsCgModule& cg) {
    assert(0);
}

Function* dotProductFunc(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto leftVec = left->type->asVec();
    const auto name = LGS_PREFIX + leftVec->getName() + leftVec->baseType->getName() + "Dot";
    auto func = cg.IRModule->getFunction(name);
    if (func) return func;

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;

    // Get new func
    const auto params = {left->type->getIRType(cg), right->type->getIRType(cg)};
    func = cg.getFunc(name, cg.getFT(cg.floatTy(), params));
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    const auto l = func->getArg(0);
    const auto r = func->getArg(1);
    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));

    const auto mulX = cg.builder.CreateFMul(lx, rx);
    const auto mulY = cg.builder.CreateFMul(ly, ry);
    Value* result = cg.builder.CreateFAdd(mulX, mulY);
    const auto vectorDim = leftVec->dimVec;
    if (vectorDim == 3) {
        const auto lz = cg.builder.CreateExtractElement(l, cg.i32(2));
        const auto rz = cg.builder.CreateExtractElement(r, cg.i32(2));
        const auto mulZ = cg.builder.CreateFMul(lz, rz);
        result = cg.builder.CreateFAdd(result, mulZ);
    } else if (vectorDim == 4) {
        const auto lw = cg.builder.CreateExtractElement(l, cg.i32(3));
        const auto rw = cg.builder.CreateExtractElement(r, cg.i32(3));
        const auto mulW = cg.builder.CreateFMul(lw, rw);
        result = cg.builder.CreateFAdd(result, mulW);
    }
    cg.builder.CreateRet(result);

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Function* crossProductFunc(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto leftVec = left->type->asVec();
    const auto name = LGS_PREFIX + leftVec->getName() + leftVec->baseType->getName() + "Cross";
    auto func = cg.IRModule->getFunction(name);
    if (func) return func;

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;

    // Get new func
    const auto vecTy = leftVec->getIRType(cg);
    const auto params = {left->type->getIRType(cg), right->type->getIRType(cg)};
    func = cg.getFunc(name, cg.getFT(vecTy, params));
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    const auto l = func->getArg(0);
    const auto r = func->getArg(1);
    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto lz = cg.builder.CreateExtractElement(l, cg.i32(2));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));
    const auto rz = cg.builder.CreateExtractElement(r, cg.i32(2));

    const auto cx = cg.builder.CreateFSub(cg.builder.CreateFMul(ly, rz), cg.builder.CreateFMul(lz, ry));
    const auto cy = cg.builder.CreateFSub(cg.builder.CreateFMul(lz, rx), cg.builder.CreateFMul(lx, rz));
    const auto cz = cg.builder.CreateFSub(cg.builder.CreateFMul(lx, ry), cg.builder.CreateFMul(ly, rx));

    Value* result = UndefValue::get(vecTy);
    result = cg.builder.CreateInsertElement(result, cx, cg.i32(0));
    result = cg.builder.CreateInsertElement(result, cy, cg.i32(1));
    result = cg.builder.CreateInsertElement(result, cz, cg.i32(2));
    cg.builder.CreateRet(result);

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    return func;
}
