#include "types/primitives/LgsULong.h"

#include <assert.h>
#include <stdint.h>

#include "exprs/constants/LgsIntConst.h"
#include "codegen/LgsCodeGen.h"
#include "types/primitives/LgsAny.h"

size_t LgsULong::sizeBytes() {
    return sizeof(uint64_t);
}

Type* LgsULong::getIRType(LgsCodeGen& cg) {
    return cg.i64Ty();
}

std::string LgsULong::getName() {
    return name;
}

LgsExpr* LgsULong::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsULong::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    return name == other->getName();
}

LgsType* LgsULong::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

Value* LgsULong::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    return cg.zero64();
}

DIType* LgsULong::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsULong::fmtStr() const {
    return "%" PRIu64;
}

void LgsULong::asIRText(LgsStrBuilder& sb, Value* value) {
    const auto buffer = sb.cg.emptyBuffer(128);
    const auto bytesRead = sb.cg.callSnprintf(fmtStr(), buffer, sb.cg.usize(128), value);
    sb.add(buffer, sb.cg.toSize(bytesRead));
}


Value* LgsULong::hashValue(LgsCodeGen& cg, Value* value) {
    return value;
}