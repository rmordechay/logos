#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "types/LgsFuncType.h"

class LgsMethodImpl : public LgsFunc {
public:
    LgsMethodImpl* implements = nullptr;

    LgsMethodImpl(const string& name, const string& parentName, LgsType* rt) {
        funcType.name = name;
        funcType.parentName = parentName;
        funcType.rt = rt;
        funcType.isMethod = true;
    }
    FunctionType* getIRFuncType(const CodeGenMetadata* metadata) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
