#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsChar.h"

LgsStr::LgsStr(): LgsIterable(&LGS_CHAR) {
    lenFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        return cg.callStrLen(args[0]->IRValue);
    };
    isEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        const auto strLen = cg.callStrLen(args[0]->IRValue);
        return cg.builder.CreateICmpEQ(strLen, cg.builder.getInt64(0));
    };
    isNotEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        const auto strLen = cg.callStrLen(args[0]->IRValue);
        return cg.builder.CreateICmpNE(strLen, cg.builder.getInt64(0));
    };
    addMethod(lenFunc);
    addMethod(isEmptyFunc);
    addMethod(isNotEmptyFunc);
    isSliceable = true;
    rtt = RTT_STR;
}

Type* LgsStr::getIRBaseType(LgsLLVMGen* cg) const {
    return ArrayType::get(baseType->getIRType(*cg), sizeExpr->getConstInt());
}

Type* LgsStr::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

uint16_t LgsStr::getUnpackCount() const {
    return 1;
}

std::string LgsStr::getName() {
    return name;
}

json::value LgsStr::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

std::string LgsStr::pname() {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

std::string LgsStr::strFormatPart() const {
    return "%s";
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

bool LgsStr::canApplyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    switch (op) {
    case ADD:
        return other->isNumber || name == IRName;
    case SUB:
        break;
    case MUL:
        break;
    case DIV:
        break;
    case MOD:
        break;
    case EQ:
        break;
    case NE:
        break;
    case LT:
        break;
    case GT:
        break;
    case GE:
        break;
    case LE:
        break;
    case AND:
        break;
    case OR:
        break;
    case BIT_AND:
        break;
    case BIT_OR:
        break;
    case BIT_XOR:
        break;
    case LSHIFT:
        break;
    case RSHIFT:
        break;
    case IN:
        break;
    case NOOP:
        break;
    }
    return false;
}

Value* LgsStr::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    if (const auto selfStr = self->asStrConst()) {
        if (const auto otherStr = other->asStrConst()) {
            return cg.getIRStr(selfStr->value + otherStr->value);
        }
        if (const auto intConst = other->asIntConst()) {
            return cg.getIRStr(selfStr->value + std::to_string(intConst->value));
        }
        if (const auto floatConst = other->asFloatConst()) {
            return cg.getIRStr(selfStr->value + std::to_string(floatConst->value));
        }
        assert(0);
    }
    const auto selfSize = IRLength(cg, self);
    const auto otherSize = IRLength(cg, other);
    auto newStrSize = cg.builder.CreateAdd(selfSize, otherSize);
    newStrSize = cg.builder.CreateAdd(newStrSize, cg.i64(1));
    const auto newStrPtr = cg.builder.CreateAlloca(cg.i8Ty(), newStrSize);
    cg.callMemCpy(newStrPtr, self->IRValue, selfSize);
    const auto dstPtr = cg.builder.CreateInBoundsGEP(cg.i8Ty(), newStrPtr, selfSize);
    cg.callMemCpy(dstPtr, other->IRValue, otherSize);
    // const auto endPtr = cg.builder.CreateInBoundsGEP(cg.i8Ty(), newStrPtr, newStrSize);
    // cg.builder.CreateStore(cg.i8(0), endPtr);
    return newStrPtr;
}

Value* LgsStr::IRLength(LgsLLVMGen& cg, LgsExpr* iterable) {
    return lenFunc->call(cg, {iterable});
}

Value* LgsStr::IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return isEmptyFunc->call(*cg, {iterable});
}

Value* LgsStr::IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*cg, {iterable});
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto iter = other->asIterable()) {
        return iter->baseType && iter->baseType->asChar();
    }
    return name == other->getName();
}
