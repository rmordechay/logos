#include <llvm/IR/Module.h>

#include "Lgs_Exprs.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsAny.h"
#include "types/LgsNullable.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRType(LgsCodeGen& cg) {
    return cg.getStructType({cg.sizeTy(), cg.ptrTy()}, name);
}

std::string LgsStr::getBaseName() {
    return name;
}

std::string LgsStr::getName() {
    return name;
}

size_t LgsStr::sizeBytes() {
    return sizeof(Lgs_StrExpr);
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

Value* LgsStr::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.allocStrConst(cg.emptyStr());
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (other->asGenericType()) return true;
    if (const auto sArr = other->asSArray()) return sArr->baseType && sArr->baseType->asChar();
    if (const auto nullable = other->asNullable()) return canCastTo(nullable->baseType);
    return name == other->getName();
}

LgsType* LgsStr::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case ADD: {
        if (rightType->asStr() || rightType->asChar() || rightType->isNumber()) {
            return new LgsStr();
        }
        break;
    }
    case IN: {
        if (equals(rightType)) return &LGS_BOOL;
        const auto rightIterable = rightType->asIterable();
        if (rightIterable && canCastTo(rightIterable->baseType)) return &LGS_BOOL;
    }
    case EQ: {
        if (equals(rightType)) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsStr::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable, {cg.zero32(), index});
    return cg.load(cg.i8Ty(), gep);
}

std::string LgsStr::fmtStr() const {
    return "%s";
}

bool LgsStr::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsStr::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto ty = getIRType(cg);
    const auto leftStrConst = left->getConstStr();
    const auto alloc = cg.allocInCurrent(IRSize(cg), true);
    if (leftStrConst.has_value()) {
        const auto lv = leftStrConst.value();
        // Str
        const auto rStr = right->getConstStr();
        if (rStr.has_value()) {
            const auto str = cg.getString(lv + rStr.value());
            cg.storeStructField(ty, alloc, rttIndices.data, str);
            return alloc;
        }
        // Int
        const auto rInt = right->getConstInt();
        if (rInt.has_value()) {
            const auto str = cg.getString(lv + std::to_string(rInt.value()));
            cg.storeStructField(ty, alloc, rttIndices.data, str);
            return alloc;
        }
        // Float
        const auto rFloat = right->getConstFloat();
        if (rFloat.has_value()) {
            const auto str = cg.getString(lv + std::to_string(rFloat.value()));
            cg.storeStructField(ty, alloc, rttIndices.data, str);
            return alloc;
        }
    }

    Value* ptr = nullptr;
    const auto leftPtr = loadStrPtr(cg, left->loadIR(cg));
    const auto leftSize = lenIR(cg, leftPtr);
    if (right->type->asChar()) {
        const auto allocSize = cg.builder.CreateAdd(leftSize, cg.usize(2));
        ptr = cg.allocInCurrent(allocSize, false);
        const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), ptr, leftSize);
        cg.callMemcpy(ptr, leftPtr, leftSize);
        cg.store(right->IRValue, rightPos);
    } else if (right->type->asStr()) {
        const auto rightPtr = loadStrPtr(cg, right->IRValue);
        const auto rightSize = lenIR(cg, rightPtr);
        const auto sumSize = cg.builder.CreateAdd(leftSize, rightSize);
        const auto allocSize = cg.builder.CreateAdd(sumSize, cg.usize(1));
        ptr = cg.allocInCurrent(allocSize, false);
        const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), ptr, leftSize);
        cg.callMemcpy(ptr, leftPtr, leftSize);
        cg.callMemcpy(rightPos, rightPtr, rightSize);
    } else {
        assert(0);
    }
    cg.storeStructField(ty, alloc, rttIndices.data, ptr);
    return alloc;
}

Value* LgsStr::lenIR(LgsCodeGen& cg, Value* iterable) {
    if (iterable->getType()->isIntegerTy() && cg.getAllocSize(iterable->getType()) == sizeof(char)) {
        return cg.usize(1);
    }
    return cg.callStrlen(iterable);
}

Value* LgsStr::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr, value});
    return cg.builder.CreateIsNotNull(rv);
}

Value* LgsStr::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.callHash(loadStrPtr(cg, value));
}

Value* LgsStr::loadStrPtr(LgsCodeGen& cg, Value* value) {
    return cg.loadStructField(getIRType(cg), value, rttIndices.data, cg.ptrTy());
}

DIType* LgsStr::getDebugType(LgsCodeGen& cg) {
    const auto& diBuilder = cg.debugger.diBuilder;
    const auto charType = diBuilder->createBasicType("char", sizeof(char), dwarf::DW_ATE_signed_char);
    return diBuilder->createPointerType(charType, sizeof(void*));
}
