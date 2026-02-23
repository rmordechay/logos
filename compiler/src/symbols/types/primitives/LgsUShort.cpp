#include "types/primitives/LgsUShort.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"

size_t LgsUShort::sizeBytes() {
    return sizeof(uint16_t);
}

Type* LgsUShort::getIRType(LgsCodeGen& cg) {
    return cg.i16Ty();
}

std::string LgsUShort::getName() {
    return name;
}

LgsExpr* LgsUShort::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsUShort::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    const auto IRName = other->getName();
    return name == IRName;
}

LgsType* LgsUShort::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsUShort::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsUShort::fmtStr() const {
    return "%d";
}

void LgsUShort::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(128);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(128), value);
    sb.add(buffer, sb.cg.toSize(bytesRead));
}
