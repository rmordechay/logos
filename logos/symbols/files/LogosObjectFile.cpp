#include "LogosObjectFile.h"

#include "application/LogosUtils.h"

void LogosObjectFile::initModule(IRBuilder<>& builder, LogosStack& theStack) {
    vector<Type*> elementTypes;
    for (int i = 0; i < obj->fields.size(); ++i) {
        const auto field = obj->fields[i];
        auto fieldType = field->type->getLLVMType(&builder);
        elementTypes.push_back(fieldType);
        theStack.addSymbol(field->name, new LogosSymbol(fieldType, i));
    }
    const auto userStruct = StructType::create(builder.getContext(), elementTypes);
    theStack.globalSymbols[name] = new LogosSymbol(userStruct);
}

Module* LogosObjectFile::generateModule(IRBuilder<>& builder, LogosStack& theStack) {
    const auto module = new Module(name, builder.getContext());
    for (const auto func : obj->funcs) {
        func->getLLVMValue(&builder, &theStack, module);
    }
    return module;
}

LogosObjectFile::~LogosObjectFile() {
    delete obj;
}

