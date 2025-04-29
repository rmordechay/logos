#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsMethodImpl : public LgsFunc {
public:
    bool isPublic = false;
    string filePath;

    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam>& params = {}) : LgsFunc(name, funcType, params, parentName) {}
    void setIRFuncType(const CodeGenMetadata* metadata) override;
    void setIRFuncParams(Argument* args) override;
    bool isEqual(const LgsFuncCall* funcCall) override;
    bool isEqual(const LgsFuncSignature* other) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
