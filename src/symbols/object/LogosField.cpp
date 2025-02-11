#include "object/LogosField.h"

Value* LogosField::getLLVMValue(CodeGenMetadata* metadata) {
    metadata->theStack->addGlobalSymbol(name, LogosSymbol(FIELD, this));
    return new GlobalVariable(
        *metadata->module,
        metadata->builder->getInt32Ty(),
        false,
        GlobalValue::ExternalLinkage,
        ConstantInt::get(metadata->builder->getInt32Ty(), 0)
    );
}
