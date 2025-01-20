#include "LogosObjectFile.h"

#include "LogosUtils.h"

Module* LogosObjectFile::generateModule(const TargetMachine& targetMachine, IRBuilder<>& builder) {
    LogosStack rootFrame;
    rootFrame.push(LogosStackFrame());

    auto& context = builder.getContext();
    auto module = Utils::createEmptyLLVMModule(name, context, targetMachine);

    vector<Type*> elementTypes;
    for (int i = 0; i < obj->fields.size(); ++i) {
        const auto field = obj->fields[i];
        auto fieldType = field->type->getLLVMType(&builder);
        elementTypes.push_back(fieldType);
        rootFrame.addSymbol(field->name, new LogosSymbol(fieldType, i));
    }

    const auto userStruct = StructType::create(context, elementTypes);
    rootFrame.addSymbol(LOGOS_THIS, new LogosSymbol(userStruct));

    for (const auto func : obj->funcs) {
        func->getLLVMValue(&builder, &rootFrame, module);
    }

    return module;
}
