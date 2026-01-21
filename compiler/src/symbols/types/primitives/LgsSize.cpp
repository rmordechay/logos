#include "types/primitives/LgsSize.h"

#include <llvm/IR/Module.h>

#include "LgsBinaryTokens.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

size_t LgsSize::sizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsCgModule& cg) {
    return cg.sizeTy();
}

std::string LgsSize::getName() {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    return new LgsIntConst(this, 0);
}

LgsType* LgsSize::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->isNumber()) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MODULO: {
        if (rightType->asDouble()) return &LGS_DOUBLE;
        if (rightType->asFloat()) return &LGS_FLOAT;
        return &LGS_SIZE;
    }
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: {
        return &LGS_SIZE;
    }
    case POW: {
        return &LGS_DOUBLE;
    }
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE: {
        return &LGS_BOOL;
    }
    case NOOP:
        assert(0);
    default:
        break;
    }
    return nullptr;

}

Constant* LgsSize::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), cg.getAllocSize(getIRType(cg)), RTT_SIZE);
}

bool LgsSize::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}

std::string LgsSize::fmtStr() const {
    return "%zu";
}

DIType* LgsSize::getDebugType(LgsCgModule& cg) {
    assert(0);
}