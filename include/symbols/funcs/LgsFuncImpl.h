#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsFuncImpl final : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* funcType, const vector<LgsParam>& params = {}) : LgsFunc(name, funcType, params) {}
    Function* getIRFunc(const CodeGenMetadata* metadata) override;
    ~LgsFuncImpl() override = default;
};

inline Function* LgsFuncImpl::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) {
        for (int i = 0; i < signature.params.size(); ++i) {
            auto paramIRType = signature.params[i].type->getIRType();
            IRParamsTypes.emplace_back(paramIRType);
        }
        IRFuncType = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    }
    auto func = metadata->module->getOrInsertFunction(signature.IRName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

#endif //LOGOSFUNCIMPL_H
