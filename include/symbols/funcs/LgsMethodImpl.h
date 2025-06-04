#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "types/LgsFuncType.h"

class LgsMethodImpl : public LgsFunc {
public:
    LgsMethodImpl* implements = nullptr;

    LgsMethodImpl(const string& name, const string& parentName, LgsType* rt, const vector<LgsParam*>& params = {}) {
        funcType.name = name;
        funcType.parentName = parentName;
        funcType.rt = rt;
        funcType.params = params;
        funcType.isMethod = true;
    }
    FunctionType* getIRFuncType(LgsRuntime* runtime) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
