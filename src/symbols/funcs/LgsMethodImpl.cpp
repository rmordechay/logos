#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

FunctionType* LgsMethodImpl::getIRFuncType(LgsRuntime* runtime) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        auto paramIRType = funcType.params[i]->type->getIRType();
        if (i == 0 && !funcType.isStatic) {
            IRParamsTypes.emplace_back(PointerType::getUnqual(context));
        } else {
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    IRFuncType = FunctionType::get(funcType.rt->getIRType(), IRParamsTypes, funcType.isVariadic);
    return IRFuncType;
}
