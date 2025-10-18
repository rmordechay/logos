#include "exprs/LgsNull.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/Module.h>

void LgsNull::completeType(LgsType* toType) {
    const auto otherNullable = toType->asNullable();
    if (!otherNullable) return;
    type->asNullable()->baseType = otherNullable->baseType;
}

std::string LgsNull::asText() {
    return LGS_NULL_LITERAL;
}

LgsNull::~LgsNull() {
    freeType(type);
    type = nullptr;
}
