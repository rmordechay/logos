#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsFuncImpl final : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params) {
        signature.setNameFromParams();
    }
    void setIRFuncType() override;
    ~LgsFuncImpl() override = default;
};

inline void LgsFuncImpl::setIRFuncType() {
    for (int i = 0; i < signature.params.size(); ++i) {
        auto paramIRType = signature.params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    IRFuncType = FunctionType::get(signature.rt->getIRType(), IRParamsTypes, false);
}

#endif //LOGOSFUNCIMPL_H
