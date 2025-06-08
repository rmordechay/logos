#include "exprs/unary/LgsInstance.h"
#include "codegen/CodeGenerator.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(LgsRuntime* runtime) {
    const auto objIRType = obj->getIRType(runtime);
    if (isReturnExpr) {
        setReturnExpr(runtime, objIRType);
    } else {
        IRValue = runtime->builder.CreateAlloca(objIRType);
    }
    for (const auto arg : args) {
        const auto field = obj->getField(arg->name);
        field->setFieldIRValue(runtime, arg->expr, IRValue);
    }
    return IRValue;
}

void LgsInstance::setReturnExpr(LgsRuntime* runtime, Type* objIRType) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (currentFunc->funcType.swapReturn) {
        IRValue = currentFunc->getReturnSwapParam()->IRValue;
    } else {
        IRValue = runtime->builder.CreateMalloc(
            Type::getInt64Ty(context),
            objIRType,
            ConstantExpr::getSizeOf(objIRType),
            ConstantInt::get(Type::getInt64Ty(context), 1)
        );
        runtime->addAllocatedExpr(this);
    }
}

void LgsInstance::free(LgsRuntime* runtime) {
    if (!isReturnExpr) {
        runtime->builder.CreateFree(IRValue);
    }
}
