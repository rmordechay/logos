#include "object/LogosField.h"

#include "object/LogosObject.h"

#include <llvm/IR/Module.h>

Value* LogosField::computeIRValue(CodeGenMetadata* metadata) {
    metadata->theStack->addGlobalSymbol(name, LogosSymbol(FIELD, this));
    return nullptr;
}
