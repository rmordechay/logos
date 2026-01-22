#include <llvm/IR/Module.h>

#include "Lgs_Exprs.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRType(LgsCgModule& cg) {
    return cg.getStructType({cg.sizeTy(), cg.ptrTy()}, name);
}

std::string LgsStr::getBaseName() {
    return name;
}

std::string LgsStr::getName() {
    return name;
}

size_t LgsStr::sizeBytes() {
    return sizeof(Lgs_Str);
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

Constant* LgsStr::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), RTT_STR);
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (other->asGenericType()) return true;
    if (const auto sArr = other->asSArray()) {
        return sArr->baseType && sArr->baseType->asChar();
    }
    return name == other->getName();
}

LgsType* LgsStr::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case ADD: {
        if (rightType->asStr() || rightType->asChar() || rightType->isNumber()) {
            const auto str = new LgsStr();
            str->isHeapAlloc = true;
            return str;
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

Value* LgsStr::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable, {cg.i32Zero(), index});
    return cg.load(cg.i8Ty(), gep);
}

std::string LgsStr::fmtStr() const {
    return "\"%s\"";
}

bool LgsStr::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsStr::addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto leftStrConst = left->getConstStr();
    if (leftStrConst.has_value()) {
        const auto lv = leftStrConst.value();
        // Str
        const auto rStr = right->getConstStr();
        if (rStr.has_value()) return cg.getString(lv + rStr.value());
        // Int
        const auto rInt = right->getConstInt();
        if (rInt.has_value()) return cg.getString(lv + std::to_string(rInt.value()));
        // Float
        const auto rFloat = right->getConstFloat();
        if (rFloat.has_value()) return cg.getString(lv + std::to_string(rFloat.value()));
    }

    const auto leftPtr = cg.builder.CreateExtractValue(left->loadIR(cg), 1);
    const auto leftSize = lenIR(cg, leftPtr);
    Value* ptr;
    if (right->type->asChar()) {
        const auto allocSize = cg.builder.CreateAdd(leftSize, cg.usize(2));
        ptr = cg.heapAlloc(allocSize, cg.currentLevel, false);
        const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), ptr, leftSize);
        cg.callMemcpy(ptr, leftPtr, leftSize);
        cg.store(right->IRValue, rightPos);
    } else {
        const auto rightPtr = cg.builder.CreateExtractValue(right->IRValue, 1);
        const auto rightSize = lenIR(cg, rightPtr);
        const auto sumSize = cg.builder.CreateAdd(leftSize, rightSize);
        const auto allocSize = cg.builder.CreateAdd(sumSize, cg.usize(1));
        ptr = cg.heapAlloc(allocSize, cg.currentLevel, false);
        const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), ptr, leftSize);
        cg.callMemcpy(ptr, leftPtr, leftSize);
        cg.callMemcpy(rightPos, rightPtr, rightSize);
    }

    const auto ty = getIRType(cg);
    const auto alloc = cg.builder.CreateAlloca(ty);
    cg.storeStructField(ty, alloc, 0, cg.currentLevel);
    cg.storeStructField(ty, alloc, 1, ptr);
    return alloc;
}

Value* LgsStr::lenIR(LgsCgModule& cg, Value* iterable) {
    if (iterable->getType()->isIntegerTy() && cg.getAllocSize(iterable->getType()) == sizeof(char)) {
        return cg.usize(1);
    }
    return cg.callStrLen(iterable);
}

Value* LgsStr::inIR(LgsCgModule& cg, Value* iterableExpr, Value* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr, value});
    return cg.builder.CreateIsNotNull(rv);
}

DIType* LgsStr::getDebugType(LgsCgModule& cg) {
    const auto& diBuilder = cg.debugger.diBuilder;
    const auto charType = diBuilder->createBasicType("char", sizeof(char), dwarf::DW_ATE_signed_char);
    return diBuilder->createPointerType(charType, sizeof(void*));
}
