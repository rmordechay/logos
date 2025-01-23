#include "LogosObjectFile.h"

#include "application/LogosUtils.h"

Module* LogosObjectFile::generateModule(IRBuilder<>& builder, LogosStack& theStack) {
    auto& context = builder.getContext();
    const auto module = new Module(name, context);
    for (const auto func : obj->funcs) {
        func->getLLVMValue(&builder, &theStack, module);
    }
    return module;
}

void LogosObjectFile::initModule(IRBuilder<>& builder, LogosStack& theStack) {
    vector<Type*> elementTypes;
    for (int i = 0; i < obj->fields.size(); ++i) {
        const auto field = obj->fields[i];
        auto fieldType = field->type->getLLVMType(&builder);
        elementTypes.push_back(fieldType);
        theStack.addSymbol(field->name, new LogosSymbol(fieldType, i));
    }
    const auto userStruct = StructType::create(builder.getContext(), elementTypes);
    theStack.addSymbol(name, new LogosSymbol(userStruct));
}

LogosObjectFile::~LogosObjectFile() {
    delete obj;
}

