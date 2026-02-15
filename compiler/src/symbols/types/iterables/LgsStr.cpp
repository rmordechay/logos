#include <llvm/IR/Module.h>
#include "LgsRTTIndices.h"
#include "Lgs_Exprs.h"
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
        if (rightType->asStr() || rightType->asChar() || rightType->isScalar()) {
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

std::optional<int64_t> LgsStr::getConstLength() {
    if (length == 0) return std::nullopt;
    return length;
}

void LgsStr::getAsIRText(LgsCodeGen& cg, LgsStrBuilder& strBuilder, Value* ptr) {
    ptr = loadRTData(cg, cg.loadPtr(ptr));
    strBuilder.add(cg, ptr, cg.callStrlen(ptr));
}

Value* LgsStr::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    return cg.builder.CreateGEP(cg.i8Ty(), loadRTData(cg, iterable), {cg.zero32(), index});
}

std::string LgsStr::fmtStr() const {
    return "%s";
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
            cg.storeStructField(ty, alloc, LgsStrIndices::data, str);
            return alloc;
        }
        // Int
        const auto rInt = right->getConstInt();
        if (rInt.has_value()) {
            const auto str = cg.getString(lv + std::to_string(rInt.value()));
            cg.storeStructField(ty, alloc, LgsStrIndices::data, str);
            return alloc;
        }
        // Float
        const auto rFloat = right->getConstFloat();
        if (rFloat.has_value()) {
            const auto str = cg.getString(lv + std::to_string(rFloat.value()));
            cg.storeStructField(ty, alloc, LgsStrIndices::data, str);
            return alloc;
        }
    }

    Value* ptr = nullptr;
    const auto leftPtr = loadRTData(cg, left->IRValue);
    const auto leftSize = lenIR(cg, leftPtr);
    if (right->type->asChar()) {
        const auto allocSize = cg.builder.CreateAdd(leftSize, cg.usize(2));
        ptr = cg.allocInCurrent(allocSize, false);
        const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), ptr, leftSize);
        cg.callMemcpy(ptr, leftPtr, leftSize);
        cg.store(right->IRValue, rightPos);
    } else if (right->type->asStr()) {
        const auto rightPtr = loadRTData(cg, right->IRValue);
        const auto rightSize = lenIR(cg, rightPtr);
        const auto sumSize = cg.builder.CreateAdd(leftSize, rightSize);
        const auto allocSize = cg.builder.CreateAdd(sumSize, cg.usize(1));
        ptr = cg.allocInCurrent(allocSize, false);
        assert(ptr->getType()->isPointerTy());
        const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), ptr, leftSize);
        cg.callMemcpy(ptr, leftPtr, leftSize);
        cg.callMemcpy(rightPos, rightPtr, rightSize);
    } else {
        assert(0);
    }
    cg.storeStructField(ty, alloc, LgsStrIndices::data, ptr);
    assert(alloc->getType()->isPointerTy());
    return alloc;
}

Value* LgsStr::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.callStrlen(iterable);
}

Value* LgsStr::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr, value});
    return cg.builder.CreateIsNotNull(rv);
}

Value* LgsStr::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.callHash(getRTType(cg), loadRTData(cg, value));
}

Value* LgsStr::loadRTData(LgsCodeGen& cg, Value* value) {
    return cg.loadStructField(getIRType(cg), value, LgsStrIndices::data, cg.ptrTy());
}

DIType* LgsStr::getDebugType(LgsCodeGen& cg) {
    const auto& diBuilder = cg.debugger.diBuilder;
    const auto charType = diBuilder->createBasicType("char", sizeof(char), dwarf::DW_ATE_signed_char);
    return diBuilder->createPointerType(charType, sizeof(void*));
}
