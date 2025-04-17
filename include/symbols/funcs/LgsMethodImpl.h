#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsMethodImpl : public LgsFunc {
public:
    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam>& params = {}) : LgsFunc(name, funcType, params, parentName) {}
    Function* getIRFunc(const CodeGenMetadata* metadata) override;
    ~LgsMethodImpl() override = default;
};

inline Function* LgsMethodImpl::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) {
        if (!signature.isStatic) {
            IRParamsTypes.emplace_back(ptrTy);
        }
        for (int i = 1; i < signature.params.size(); ++i) {
            auto paramIRType = signature.params[i].type->getIRType();
            IRParamsTypes.emplace_back(paramIRType);
        }
        IRFuncType = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    }
    auto func = metadata->module->getOrInsertFunction(signature.IRName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

#endif //LOGOSMETHODIMPL_H
