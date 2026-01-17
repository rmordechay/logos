#include "types/iterables/LgsVec.h"
#include <llvm/IR/Module.h>
#include "LgsBinaryTokens.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/LgsAny.h"
#include "cblas/cblas.h"
#include "types/iterables/LgsMatrix.h"
#include "types/primitives/LgsBool.h"
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
    return FixedVectorType::get(baseType->getIRType(cg), dimVec);
}

Constant* LgsVec::getRTType(LgsCgModule& cg) {
    const auto sv = cg.getRTTExtraStruct(getName(), {cg.ptrTy()}, {baseType->getRTType(cg)});
    if (dimVec == 2) {
        return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_VEC2, sv);
    }
    if (dimVec == 3) {
        return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_VEC3, sv);
    }
    return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_VEC4, sv);
}

std::string LgsVec::getBaseName() {
    return name + std::to_string(dimVec);
}

std::string LgsVec::getName() {
    auto s = name + std::to_string(dimVec);
    if (baseType) s += baseType->getName();
    return s;
}

std::string LgsVec::pname() {
    auto s = name + std::to_string(dimVec);
    if (baseType) s += '<' + baseType->getName() + '>';
    else s += LGS_UNKNOWN_TYPE;
    return s;
}

size_t LgsVec::sizeBytes() {
    return baseType->sizeBytes() * 2;
}

bool LgsVec::equals(LgsType* other) {
    if (!baseType) return false;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    if (dimVec != otherVec->dimVec) return false;
    return baseType->equals(other);
}

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr(this);
}

bool LgsVec::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->getName() == LgsAny::name) return true;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    return dimVec == otherVec->dimVec && baseType->canCastTo(otherVec->baseType);
}

LgsType* LgsVec::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!baseType) return nullptr;
    const auto otherVec = rightType->asVec();
    switch (op.opType) {
    case ADD:
    case SUB:
    case MODULO: {
        if (otherVec) {
            if (baseType->isFloat || otherVec->baseType->isFloat) return new LgsVec(dimVec, &LGS_FLOAT);
            if (baseType->sizeBytes() >= otherVec->baseType->sizeBytes()) return this;
            return new LgsVec(dimVec, otherVec->baseType);
        }
        if (rightType->isScalar()) {
            if (baseType->isFloat || rightType->isFloat) return new LgsVec(dimVec, &LGS_FLOAT);
            if (baseType->sizeBytes() >= rightType->sizeBytes()) return this;
            return new LgsVec(dimVec, rightType);
        }
        break;
    }
    case DIV:
        if (otherVec) return new LgsVec(dimVec, &LGS_FLOAT);
        if (rightType->isScalar()) return new LgsVec(dimVec, &LGS_FLOAT);
        break;
    case MUL:
        if (otherVec && canCastTo(rightType)) return &LGS_FLOAT; // dot product
        if (rightType->isScalar()) {
            if (baseType->isFloat || rightType->isFloat) return new LgsVec(dimVec, &LGS_FLOAT);
            if (baseType->sizeBytes() >= rightType->sizeBytes()) return this;
            return new LgsVec(dimVec, rightType);
        }
        break;
    case CROSS: {
        if (dimVec == 3 && canCastTo(rightType)) return new LgsVec(3, &LGS_FLOAT);
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
    std::vector<LgsType*> types;
    for (const auto arg : args) types.push_back(arg->type);
    baseType = getBiggestIntType(types);
    return !!baseType;
}

Value* LgsVec::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto rtype = right->type;
    const auto isScalar = rtype->isScalar();
    if (baseType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left->loadIR(cg), right->loadIR(cg), left->type, right->type);
        if (isScalar) r = cg.builder.CreateVectorSplat(dimVec, r);
        return cg.builder.CreateFAdd(l, r);
    }
    const auto l = left->loadIR(cg);
    auto r = right->loadIR(cg);
    if (isScalar) r = cg.builder.CreateVectorSplat(dimVec, r);
    return cg.builder.CreateAdd(l, r);
}

Value* LgsVec::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto rtype = right->type;
    const auto isScalar = rtype->isScalar();
    if (baseType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left->loadIR(cg), right->loadIR(cg), left->type, right->type);
        if (isScalar) r = cg.builder.CreateVectorSplat(dimVec, r);
        return cg.builder.CreateFSub(l, r);
    }
    const auto l = left->loadIR(cg);
    auto r = right->loadIR(cg);
    if (isScalar) r = cg.builder.CreateVectorSplat(dimVec, r);
    return cg.builder.CreateSub(l, r);
}

Value* LgsVec::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->asMatrix() && right->type->asVec()) {
        return matVecMul(cg, left, right);
    }
    const auto rtype = right->type;
    const auto isScalar = rtype->isScalar();
    if (baseType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left->loadIR(cg), right->loadIR(cg), left->type, right->type);
        if (isScalar) r = cg.builder.CreateVectorSplat(dimVec, r);
        return cg.builder.CreateFMul(l, r);
    }
    const auto l = left->loadIR(cg);
    auto r = right->loadIR(cg);
    if (isScalar) r = cg.builder.CreateVectorSplat(dimVec, r);
    return cg.builder.CreateMul(l, r);
}

Value* LgsVec::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    auto [l, r] = loadPairAsFloat(cg, left->loadIR(cg), right->loadIR(cg), left->type, right->type);
    if (right->type->isScalar()) {
        r = cg.builder.CreateVectorSplat(dimVec, r);
    }
    return cg.builder.CreateFDiv(l, r);
}

Value* LgsVec::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    auto [l, r] = loadPairAsFloat(cg, left->loadIR(cg), right->loadIR(cg), left->type, right->type);
    if (right->type->isScalar()) {
        r = cg.builder.CreateVectorSplat(dimVec, r);
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
        LgsIntConst tempIndex(&LGS_INT, 0);
        const auto element = getIRElement(cg, iterableExpr, &tempIndex);
        const auto eq = eqIR(cg, element, value->IRValue, baseType, baseType);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.store(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
    });
    return cg.load(cg.i1Ty(), resultPtr);
}

Value* LgsVec::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.usize(dimVec);
}

Value* LgsVec::getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) {
    Value* vec = iterable->IRValue;
    if (iterable->IRValue->getType()->isPointerTy()) {
        vec = cg.load(getIRType(cg), iterable->IRValue);
    }
    return cg.builder.CreateExtractElement(vec, index->IRValue);
}

void LgsVec::addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable->IRValue, {cg.i32Zero(), index->IRValue});
    cg.store(value->IRValue, gep);
}

Value* LgsVec::matVecMul(LgsCgModule& cg, const LgsExpr* left, LgsExpr* right) const {
    const auto mat = left->type->asMatrix();
    const auto order = cg.i32(CblasRowMajor);
    const auto transpose = cg.i32(CblasNoTrans);
    const auto m = cg.i32(mat->rows);
    const auto n = cg.i32(mat->columns);
    const auto alpha = cg.floatv(1);
    const auto matrixPtr = left->IRValue;
    const auto lda = cg.i32(mat->columns);
    const auto vectorPtr = right->IRValue;
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
    const auto rightVec = right->type->asVec();
    const auto name = LGS_PREFIX + leftVec->getName() + leftVec->baseType->getName() + "Dot";
    auto func = cg.IRModule->getFunction(name);
    if (func) return func;

    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;

    const auto params = {leftVec->getIRType(cg), rightVec->getIRType(cg)};
    func = cg.getFunc(name, cg.getFT(cg.floatTy(), params));
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    Value* l = func->getArg(0);
    Value* r = func->getArg(1);
    if (leftVec->baseType->isInt) {
        l = cg.builder.CreateSIToFP(l, FixedVectorType::get(cg.floatTy(), leftVec->dimVec));
    }
    if (rightVec->baseType->isInt) {
        r = cg.builder.CreateSIToFP(r, FixedVectorType::get(cg.floatTy(), rightVec->dimVec));
    }

    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));

    const auto mulX = cg.builder.CreateFMul(lx, rx);
    const auto mulY = cg.builder.CreateFMul(ly, ry);
    Value* result = cg.builder.CreateFAdd(mulX, mulY);
    const auto vectorDim = leftVec->dimVec;
    if (vectorDim >= 3) {
        const auto lz = cg.builder.CreateExtractElement(l, cg.i32(2));
        const auto rz = cg.builder.CreateExtractElement(r, cg.i32(2));
        const auto mulZ = cg.builder.CreateFMul(lz, rz);
        result = cg.builder.CreateFAdd(result, mulZ);
    }
    if (vectorDim == 4) {
        const auto lw = cg.builder.CreateExtractElement(l, cg.i32(3));
        const auto rw = cg.builder.CreateExtractElement(r, cg.i32(3));
        const auto mulW = cg.builder.CreateFMul(lw, rw);
        result = cg.builder.CreateFAdd(result, mulW);
    }
    cg.builder.CreateRet(result);

    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Function* crossProductFunc(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto leftVec = left->type->asVec();
    const auto rightVec = right->type->asVec();
    const auto name = LGS_PREFIX + leftVec->getName() + leftVec->baseType->getName() + "Cross";
    auto func = cg.IRModule->getFunction(name);
    if (func) return func;

    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;

    // Get new func
    const auto vecTy = FixedVectorType::get(cg.floatTy(), 3);
    const auto params = {left->type->getIRType(cg), right->type->getIRType(cg)};
    func = cg.getFunc(name, cg.getFT(vecTy, params));
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    Value* l = func->getArg(0);
    Value* r = func->getArg(1);
    if (leftVec->baseType->isInt) {
        l = cg.builder.CreateSIToFP(l, FixedVectorType::get(cg.floatTy(), leftVec->dimVec));
    }
    if (rightVec->baseType->isInt) {
        r = cg.builder.CreateSIToFP(r, FixedVectorType::get(cg.floatTy(), rightVec->dimVec));
    }

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
