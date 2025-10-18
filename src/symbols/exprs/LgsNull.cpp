#include "exprs/LgsNull.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/Module.h>

std::string LgsNull::asText() {
    return LGS_NULL_LITERAL;
}

LgsNull::~LgsNull() {
    freeType(type);
    type = nullptr;
}
