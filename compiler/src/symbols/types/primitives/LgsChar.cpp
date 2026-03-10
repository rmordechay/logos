#include <string>

#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/primitives/LgsAny.h"
#include "types/iterables/LgsStr.h"
#include "LgsType.h"
#include "types/primitives/LgsChar.h"


size_t LgsChar::sizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsCodeGen& cg) {
    return cg.i8Ty();
}

std::string LgsChar::getName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

std::string LgsChar::fmtStr() const {
    return "'%c'";
}

LgsType* LgsChar::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

bool LgsChar::canCastTo(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsStr::name) return true;
    return name == IRName;
}

DIType* LgsChar::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

void LgsChar::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(2);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(2), value);
    sb.add(buffer, sb.cg.toSize(bytesRead));
}

Value* LgsChar::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    return cg.i8('0');
}

Value* LgsChar::hashValue(LgsCodeGen& cg, Value* value) {
    return value;
}
