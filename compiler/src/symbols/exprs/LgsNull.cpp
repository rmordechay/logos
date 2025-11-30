#include "exprs/LgsNull.h"
#include "codegen/LgsCgModule.h"
#include "LgsDefinitions.h"
#include <llvm/IR/Module.h>

Value* LgsNull::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsNull::castImplicitly(LgsType* toType) {}

std::string LgsNull::asText() {
    return LGS_NULL_LITERAL;
}

bool LgsNull::equals(LgsExpr* other) {
    assert(0);
}

LgsNull::~LgsNull() {
    freeType(type);
    setType(nullptr);
}
