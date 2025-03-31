#include "exprs/unary/LgsInstance.h"
#include "CodeGenerator.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return name;
}

Value* LgsInstance::createIRValue(CodeGenMetadata* metadata) {
    if (modules.find(name) == modules.end()) {
        CodeGenerator::generateModule(metadata->buildDir, obj);
    }
    const auto currentFunc = metadata->logosStack.currentFunc->getIRFunc(metadata);
    if (currentFunc->arg_size() == 0) {
        return metadata->builder.CreateAlloca(obj->getIRType());
    }
    const auto firstArg = currentFunc->arg_begin();
    if (firstArg->getName() == LOGOS_SELF) {
        return firstArg;
    }
    return nullptr;
}

LgsInstance::~LgsInstance() {
    for (const auto &field : fields) {
        delete field.second;
    }
}
