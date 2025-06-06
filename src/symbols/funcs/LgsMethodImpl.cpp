#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

FunctionType* LgsMethodImpl::getIRFuncType(LgsRuntime* runtime) {
    if (funcType.IRType) return funcType.IRType;
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        auto paramIRType = funcType.params[i]->type->getIRType();
        if (i == 0 && !funcType.isStatic) {
            IRParamsTypes.emplace_back(PointerType::getUnqual(context));
        } else {
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    Type* rt;
    if (funcType.swapReturn) {
        rt = runtime->builder.getVoidTy();
        IRParamsTypes.insert(IRParamsTypes.begin() + funcType.returnParamIndex, PointerType::getUnqual(context));
    } else {
        rt = funcType.rt->getIRType();
    }
    funcType.IRType = FunctionType::get(rt, IRParamsTypes, funcType.isVariadic);
    return funcType.IRType;
}
