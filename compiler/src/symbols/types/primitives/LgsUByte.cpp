#include "types/primitives/LgsUByte.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsAny.h"

size_t LgsUByte::sizeBytes() {
    return sizeof(uint8_t);
}

Type* LgsUByte::getIRType(LgsCodeGen& cg) {
    return cg.i8Ty();
}

std::string LgsUByte::getName() {
    return name;
}

LgsExpr* LgsUByte::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsUByte::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    const auto IRName = other->getName();
    return name == IRName;
}

LgsType* LgsUByte::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsUByte::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsUByte::fmtStr() const {
    return "%d";
}

void LgsUByte::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(128);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(128), value);
    sb.add(buffer, sb.cg.toSize(bytesRead));
}
