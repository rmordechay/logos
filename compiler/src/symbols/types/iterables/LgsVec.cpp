#include "types/iterables/LgsVec.h"
#include <llvm/IR/Module.h>
#include "LgsBinaryTokens.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/iterables/LgsMatrix.h"
#include "types/primitives/LgsBool.h"
#include <sstream>

#include "codegen/LgsCodeGen.h"
#include "exprs/LgsBinaryExpr.h"

LgsField* LgsVec::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    const size_t newFieldDim = fieldName.size();
    LgsField* field = nullptr;
    if (newFieldDim == 1) {
        field = new LgsField(fieldName, baseType);
        field->index = getComponentIndex(fieldName[0]);
    } else {
        field = new LgsField(fieldName, new LgsVec(newFieldDim));
    }
    fields.push_back(field);
    field->parentType = this;
    return field;
}

Type* LgsVec::getIRType(LgsCodeGen& cg) {
    return FixedVectorType::get(baseType->getIRType(cg), dimVec);
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
    s += '<' + getPrettyName(baseType) + '>';
    return s;
}

size_t LgsVec::sizeBytes() {
    return baseType->sizeBytes() * 2;
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

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr(this);
}

bool LgsVec::equals(LgsType* other) {
    if (!baseType) return false;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    if (dimVec != otherVec->dimVec) return false;
    return baseType->equals(other);
}

bool LgsVec::canCastTo(LgsType* other) {
    if (!baseType) return false;
    if (other->isAny()) return true;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    return dimVec == otherVec->dimVec && baseType->canCastTo(otherVec->baseType);
}

std::optional<int64_t> LgsVec::getConstLength() {
    return dimVec;
}

LgsType* LgsVec::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!baseType) return nullptr;
    const auto otherVec = rightType->asVec();
    switch (op.opType) {
    case ADD:
    case SUB:
    case MODULO: {
        if (otherVec) {
            if (dimVec != otherVec->dimVec) return nullptr;
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
        if (otherVec) {
            if (dimVec != otherVec->dimVec) return nullptr;
            return new LgsVec(dimVec, &LGS_FLOAT);
        }
        if (rightType->isScalar()) return new LgsVec(dimVec, &LGS_FLOAT);
        break;
    case MUL:
        if (otherVec) {
            if (dimVec != otherVec->dimVec) return nullptr;
            return &LGS_FLOAT; // dot product
        }
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

Constant* LgsVec::getRTTypeExtra(LgsCodeGen& cg) {
    const auto rttName = getRTTName();
    const auto st = cg.getStructType({cg.sizeTy(), cg.ptrTy()});
    const std::vector<Constant*> args = {cg.usize(dimVec), baseType->getRTType(cg)};
    return cg.createGlobal(rttName + "_extra", st, ConstantStruct::get(st, args));
}

Value* LgsVec::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    if (pointee) return pointee;
    return cg.builder.CreateAlloca(getIRType(cg));
}

Value* LgsVec::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto lExpr = binExpr->left;
    const auto rExpr = binExpr->right;
    auto l = lExpr->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) {
        l = cg.load(lExpr->type->getIRType(cg), l);
    }
    if (r->getType()->isPointerTy()) {
        r = cg.load(lExpr->type->getIRType(cg), r);
    }
    const auto ty = getIRType(cg);
    if (baseType->isInt) {
        if (lExpr->type->isInt) {
            l = cg.builder.CreateVectorSplat(dimVec, cg.toInt(l));
        }
        if (rExpr->type->isInt) {
            r = cg.builder.CreateVectorSplat(dimVec, cg.toInt(r));
        }
        return cg.allocaAndStore(ty, cg.builder.CreateAdd(l, r));
    }
    if (lExpr->type->isInt) {
        l = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(l));
    }
    if (rExpr->type->isInt) {
        r = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(r));
    }
    return cg.allocaAndStore(ty, cg.builder.CreateFAdd(l, r));
}

Value* LgsVec::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto lExpr = binExpr->left;
    const auto rExpr = binExpr->right;
    auto l = lExpr->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) {
        l = cg.load(lExpr->type->getIRType(cg), l);
    }
    if (r->getType()->isPointerTy()) {
        r = cg.load(lExpr->type->getIRType(cg), r);
    }
    const auto ty = getIRType(cg);
    if (baseType->isInt) {
        if (lExpr->type->isInt) {
            l = cg.builder.CreateVectorSplat(dimVec, cg.toInt(l));
        }
        if (rExpr->type->isInt) {
            r = cg.builder.CreateVectorSplat(dimVec, cg.toInt(r));
        }
        return cg.allocaAndStore(ty, cg.builder.CreateSub(l, r));
    }
    if (lExpr->type->isInt) {
        l = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(l));
    }
    if (rExpr->type->isInt) {
        r = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(r));
    }
    return cg.allocaAndStore(ty, cg.builder.CreateFSub(l, r));
}

Value* LgsVec::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto lExpr = binExpr->left;
    const auto rExpr = binExpr->right;
    auto l = lExpr->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) {
        l = cg.load(lExpr->type->getIRType(cg), l);
    }
    if (r->getType()->isPointerTy()) {
        r = cg.load(lExpr->type->getIRType(cg), r);
    }
    const auto ty = getIRType(cg);
    if (baseType->isInt) {
        if (lExpr->type->isInt) {
            l = cg.builder.CreateVectorSplat(dimVec, cg.toInt(l));
        }
        if (rExpr->type->isInt) {
            r = cg.builder.CreateVectorSplat(dimVec, cg.toInt(r));
        }
        return cg.allocaAndStore(ty, cg.builder.CreateMul(l, cg.toInt(r)));
    }
    if (lExpr->type->isInt) {
        l = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(l));
    }
    if (rExpr->type->isInt) {
        r = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(r));
    }
    return cg.allocaAndStore(ty, cg.builder.CreateFMul(l, r));
}

Value* LgsVec::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto lExpr = binExpr->left;
    const auto rExpr = binExpr->right;
    auto l = lExpr->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) {
        l = cg.load(lExpr->type->getIRType(cg), l);
    }
    if (r->getType()->isPointerTy()) {
        r = cg.load(lExpr->type->getIRType(cg), r);
    }
    const auto ty = getIRType(cg);
    if (baseType->isInt) {
        if (lExpr->type->isInt) {
            l = cg.builder.CreateVectorSplat(dimVec, cg.toInt(l));
        }
        if (rExpr->type->isInt) {
            r = cg.builder.CreateVectorSplat(dimVec, cg.toInt(r));
        }
        return cg.allocaAndStore(ty, cg.builder.CreateSDiv(l, r));
    }
    if (lExpr->type->isInt) {
        l = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(l));
    }
    if (rExpr->type->isInt) {
        r = cg.builder.CreateVectorSplat(dimVec, cg.toFloat(r));
    }
    return cg.allocaAndStore(ty, cg.builder.CreateFDiv(l, r));
}

Value* LgsVec::modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsVec::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.usize(dimVec);
}

Value* LgsVec::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    const auto found = cg.allocaAndStore(cg.i1Ty(), cg.false_());
    cg.loop(cg.i64(dimVec), [this, &cg, iterableExpr, value, found](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto element = getIRElement(cg, iterableExpr, index);
        const auto eq = eqIR(cg, element, value, baseType);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.store(cg.true_(), found);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
    });
    return cg.load(cg.i1Ty(), found);
}

Value* LgsVec::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    assert(iterable);
    return cg.builder.CreateGEP(getIRType(cg), iterable, {cg.zero32(), index});
}

void LgsVec::addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.zero32(), index});
    cg.store(value, gep);
}

Value* LgsVec::matVecMul(LgsCodeGen& cg, const LgsExpr* left, LgsExpr* right) const {
    const auto mat = left->type->asMatrix();
    const auto order = cg.i32(CBLAS_ROW_MAJOR);
    const auto transpose = cg.i32(CBLAS_NO_TRANS);
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
    const auto ft = cg.getFT(cg.voidTy(), {
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
    });
    cg.builder.CreateCall(cg.getFunc("cblas_sgemv", ft), {
        order,
        transpose,
        m,
        n,
        alpha,
        matrixPtr,
        lda,
        vectorPtr,
        incx,
        beta,
        results,
        incy
    });
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

DIType* LgsVec::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Function* getDotProductFunc(LgsCodeGen& cg, LgsVec* vecType) {
    const auto name = LGS_PREFIX + vecType->getName() + "_Dot";
    auto func = cg.IRModule->getFunction(name);
    if (func) return func;
    const auto params = {vecType->getIRType(cg), vecType->getIRType(cg)};
    func = cg.getFunc(name, cg.getFT(cg.floatTy(), params));

    cg.startFunc(func);
    Value* l = func->getArg(0);
    Value* r = func->getArg(1);

    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));

    const auto mulX = cg.builder.CreateFMul(lx, rx);
    const auto mulY = cg.builder.CreateFMul(ly, ry);
    Value* result = cg.builder.CreateFAdd(mulX, mulY);
    const auto vectorDim = vecType->dimVec;
    if (vectorDim == 3) {
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

    cg.createRet(result);
    cg.restoreFuncState();
    return func;
}

Function* getCrossProductFunc(LgsCodeGen& cg, LgsVec* vecType) {
    assert(vecType->dimVec == 3);
    const auto name = LGS_PREFIX + vecType->getName() + "_Cross";
    auto func = cg.IRModule->getFunction(name);
    if (func) return func;
    const auto ty = vecType->getIRType(cg);
    const std::vector<Type*> params = {cg.ptrTy(), ty, ty};
    func = cg.getFunc(name, cg.getFT(cg.voidTy(), params));

    cg.startFunc(func);
    Value* result = func->getArg(0);
    Value* l = func->getArg(1);
    Value* r = func->getArg(2);

    const auto lx = cg.builder.CreateExtractElement(l, cg.i32(0));
    const auto ly = cg.builder.CreateExtractElement(l, cg.i32(1));
    const auto lz = cg.builder.CreateExtractElement(l, cg.i32(2));
    const auto rx = cg.builder.CreateExtractElement(r, cg.i32(0));
    const auto ry = cg.builder.CreateExtractElement(r, cg.i32(1));
    const auto rz = cg.builder.CreateExtractElement(r, cg.i32(2));

    const auto cx = cg.builder.CreateFSub(cg.builder.CreateFMul(ly, rz), cg.builder.CreateFMul(lz, ry));
    const auto cy = cg.builder.CreateFSub(cg.builder.CreateFMul(lz, rx), cg.builder.CreateFMul(lx, rz));
    const auto cz = cg.builder.CreateFSub(cg.builder.CreateFMul(lx, ry), cg.builder.CreateFMul(ly, rx));
    cg.storeField(ty, result, 0, cx);
    cg.storeField(ty, result, 1, cy);
    cg.storeField(ty, result, 2, cz);

    cg.createRet();
    cg.restoreFuncState();
    return func;
}
