#include "types/LgsEnum.h"
#include "codegen/LgsCodeGen.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCodeGen& cg) {
    assert(0);
}

Constant* LgsEnum::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(name, IRSize(cg), rtt);
}

std::string LgsEnum::getName() {
    return name;
}

bool LgsEnum::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return name == otherName;
}

LgsType* LgsEnum::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsEnum::fmtStr() const {
    return "%s";
}

Value* LgsEnum::asIRStr(LgsCodeGen& cg, Value* v) {
    return cg.getString(name);
}

size_t LgsEnum::sizeBytes() {
    return sizeof(void*);
}

DIType* LgsEnum::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsEnum::~LgsEnum() {
    for (const auto field : fields) {
        delete field->type;
        field->type = nullptr;
    }
}
