#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>

#include "LgsBinaryTokens.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

std::string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsIntConst(&LGS_BOOL, false);
}

std::string LgsBool::fmtStr() const {
    return "%s";
}

size_t LgsBool::sizeBytes() {
    return sizeof(bool);
}

Type* LgsBool::getIRType(LgsCodeGen& cg) {
    return cg.i1Ty();
}

bool LgsBool::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (other->isAny()) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsInt::name) return true;
    if (otherName == LgsSize::name) return true;
    if (otherName == LgsLong::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsUInt::name) return true;
    return name == otherName;
}

LgsType* LgsBool::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->isScalar()) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MODULO: {
        if (rightType->asDouble()) return &LGS_DOUBLE;
        if (rightType->asFloat()) return &LGS_FLOAT;
        return &LGS_BYTE;
    }
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: return &LGS_BYTE;
    case POW: return this;
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE:
    case OR:
    case AND: return &LGS_BOOL;
    default:
        break;
    }
    return nullptr;
}

void LgsBool::asIRText(LgsStrBuilder& sb, Value* ptr) {
    auto& cg = sb.cg;
    const auto trueStr = cg.getString(trueLiteral, false);
    const auto falseStr = cg.getString(falseLiteral, false);
    const auto v = cg.builder.CreateSelect(ptr, trueStr, falseStr);
    sb.add(v, cg.callStrlen(v));
}

Value* LgsBool::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.false_();
}

Value* LgsBool::hashValue(LgsCodeGen& cg, Value* value) {
    return value;
}

DIType* LgsBool::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
