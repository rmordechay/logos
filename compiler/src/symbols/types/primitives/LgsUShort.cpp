#include "types/primitives/LgsUShort.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"

std::string LgsUShort::getName() {
    return name;
}

size_t LgsUShort::sizeBytes() {
    return sizeof(uint16_t);
}

LgsExpr* LgsUShort::getZeroValue() {
    return new LgsIntConst(this, 0);
}

std::string LgsUShort::fmtStr() const {
    return "%d";
}

void LgsUShort::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(128);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(128), value);
    sb.add(buffer, sb.cg.toSize(bytesRead));
}

bool LgsUShort::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    const auto IRName = other->getName();
    return name == IRName;
}

LgsType* LgsUShort::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

Type* LgsUShort::getIRType(LgsCodeGen& cg) {
    return cg.i16Ty();
}

Value* LgsUShort::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    return cg.zero16();
}

Value* LgsUShort::hashValue(LgsCodeGen& cg, Value* value) {
    return value;
}

DIType* LgsUShort::getDebugType(LgsCodeGen& cg) {
    assert(0);
}
