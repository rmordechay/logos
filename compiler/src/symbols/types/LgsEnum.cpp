#include "types/LgsEnum.h"

#include <assert.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

#include "LgsUtils.h"
#include "codegen/LgsCodeGen.h"
#include "stmts/LgsField.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCodeGen& cg) {
    return cg.sizeTy();
}

std::string LgsEnum::getName() {
    return name;
}

bool LgsEnum::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    return name == other->getName();
}

LgsType* LgsEnum::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsEnum::fmtStr() const {
    return "%s";
}

Value* LgsEnum::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.usize(hashString(name));
}

size_t LgsEnum::sizeBytes() {
    return sizeof(void*);
}

DIType* LgsEnum::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsEnum::~LgsEnum() {
    for (const auto field : fields) {
        field->type = nullptr;
    }
}
