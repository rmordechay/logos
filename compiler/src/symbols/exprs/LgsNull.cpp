#include "exprs/LgsNull.h"
#include "codegen/LgsLLVMGen.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <llvm/IR/Module.h>

void LgsNull::castImplicitly(LgsType* toType) {
    const auto otherNullable = toType->asNullable();
    if (!otherNullable) return;
    type->asNullable()->baseType = otherNullable->baseType;
}

std::string LgsNull::asText() {
    return LGS_NULL_LITERAL;
}

bool LgsNull::equals(LgsExpr* other) {
    assert(0);
}

Value* LgsNull::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

LgsNull::~LgsNull() {
    freeType(type);
    setType(nullptr);
}
