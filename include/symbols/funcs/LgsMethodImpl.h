#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "types/LgsMethodType.h"

class LgsMethodImpl : public LgsFunc {
public:
    string parentName;
    int vtableKey = -1;
    bool isPublic = false;
    bool isStatic = false;
    LgsMethodType methodType;
    LgsMethodImpl* implements = nullptr;

    LgsMethodImpl() = default;
    LgsMethodImpl(const string& name, const string& parentName, LgsType* rt) {
        methodType.name = name;
        methodType.parentName = parentName;
        methodType.rt = rt;
    }
    bool equals(const LgsFuncCall* other) override;
    FunctionType* getIRFuncType(const CodeGenMetadata* metadata) override;
    void setIRParams(Argument* args) override;
    LgsFuncType* getFuncType() override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
