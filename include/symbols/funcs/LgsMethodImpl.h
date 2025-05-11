#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"

class LgsMethodImpl : public LgsFunc {
public:
    LgsMethodImpl(const string& name, const string& parentName, LgsType* rt) {
        funcType.name = name;
        funcType.parentName = parentName;
        funcType.rt = rt;
    }
    FunctionType* getIRFuncType(const CodeGenMetadata* metadata) override;
    void setIRParams(Function* func, Argument* args) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
