#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsMethodImpl : public LgsFunc {
public:
    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam>& params = {}) : LgsFunc(name, funcType, params, parentName) {}
    void setIRFuncType() override;
    bool isMethodEqual(const LgsFuncSignature* otherSignature) const;
    ~LgsMethodImpl() override = default;
};

inline void LgsMethodImpl::setIRFuncType() {
    if (!signature.isStatic) {
        IRParamsTypes.emplace_back(ptrTy);
    }
    for (int i = 1; i < signature.params.size(); ++i) {
        auto paramIRType = signature.params[i].type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    IRFuncType = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
}

inline bool LgsMethodImpl::isMethodEqual(const LgsFuncSignature* otherSignature) const {
    if (signature.name != otherSignature->name) return false;
    if (signature.type->getName() != otherSignature->type->getName()) return false;
    if (signature.params.size() == 0) return true;
    for (size_t i = 0; i < signature.params.size() - 1; ++i) {
        auto thisTypeName = signature.params[i + 1].type->getName();
        auto otherTypeName = otherSignature->params[i].type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

#endif //LOGOSMETHODIMPL_H
