#include "stmts/LogosFieldDef.h"

#include "exprs/LogosInstance.h"
#include "object/LogosField.h"
#include "object/LogosObject.h"
#include "stmts/LogosVarDec.h"

#include <LogosStack.h>

Value* LogosFieldDef::computeIRValue(CodeGenMetadata* metadata) {
    // TODO make dynamic
    auto& builder = metadata->builder;
    const auto firstName = names[0];
    const auto secondName = names[1];
    const auto instance = metadata->logosStack.getSymbol(firstName)->instance;

    const auto obj = instance->obj;
    const auto objValue = instance->writeIRValue(metadata);
    const auto objType = instance->type->getIRType();

    const auto fieldPos = obj->fields[secondName]->fieldPosition;
    const auto fieldExprValue = expr->writeIRValue(metadata);
    obj->fields[secondName]->expr = expr;
    const auto gep = builder.CreateStructGEP(objType, objValue, fieldPos);
    builder.CreateStore(fieldExprValue, gep);
    return gep;
}

LogosFieldDef::~LogosFieldDef() {
    delete expr;
}


Value* createAddStructMembers(Module& module, IRBuilder<>& builder) {
    auto* structType = StructType::create(context, {Type::getInt32Ty(context), Type::getInt32Ty(context)}, "MyStruct");
    auto* funcType = FunctionType::get(Type::getInt32Ty(context), {PointerType::get(structType, 0)}, false);

    auto* func = Function::Create(funcType, Function::ExternalLinkage, "addStructMembers", &module);

    // Create a new basic block to insert the code
    auto* block = BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(block);

    // Get the function argument (struct pointer)
    auto* structArg = func->getArg(0);

    // Extract the two int32 members from the struct
    auto* field1 = builder.CreateStructGEP(structType, structArg, 0, "field1");
    auto* field2 = builder.CreateStructGEP(structType, structArg, 1, "field2");

    auto* load1 = builder.CreateLoad(Type::getInt32Ty(context), field1, "load1");
    auto* load2 = builder.CreateLoad(Type::getInt32Ty(context), field2, "load2");

    // Add the two loaded values
    auto* result = builder.CreateAdd(load1, load2, "addresult");

    // Return the result
    builder.CreateRet(result);

    return func;
}