#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

Function* LgsMethodImpl::getIRFunc(LgsRuntime* runtime) {
    const auto f = runtime->module->getFunction(funcType.getIRName());
    if (f) return f;
    const auto funcIRType = getIRFuncType(runtime);
    const auto func = Function::Create(funcIRType, GlobalValue::ExternalLinkage);;
    std::cout << runtime->module->getName().str() << ' ' << &runtime->context << std::endl;
    std::cout << funcType.name << ' ' << &func->getContext() << std::endl;
    const auto IRFunc = dyn_cast<Function>(func);
    auto args = IRFunc->arg_begin();
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        if (param->isVariadic) {
            args++->setName("argc");
        } else {
            param->setIRValue(args);
        }
        if (param->expr) param->expr->setIRValue(args);
        args->setName(param->name);
        args++;
    }
    return IRFunc;
}

FunctionType* LgsMethodImpl::getIRFuncType(LgsRuntime* runtime) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        auto paramIRType = funcType.params[i]->type->getIRType(runtime);
        if (i == 0 && !funcType.isStatic) {
            IRParamsTypes.emplace_back(runtime->builder.getPtrTy());
        } else {
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    IRFuncType = FunctionType::get(funcType.rt->getIRType(runtime), IRParamsTypes, funcType.isVariadic);
    return IRFuncType;
}
