#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "funcs/LgsParam.h"
#include "LgsType.h"

class LgsParam;

class LgsFuncType final : public LgsType {
public:
    string name;
    string IRName;
    string parentName;
    LgsType* rt = nullptr;
    vector<LgsParam*> params;
    FunctionType* IRFuncType = nullptr;
    bool isMethod = false;
    bool isStatic = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isBuiltin = false;
    bool isVariadic = false;
    bool isAnonymous = false;
    bool isRvBig = false;
    bool swapReturn = false;
    bool hasDefaultParams = false;
    int returnParamIndex = -1;

    LgsFuncType() {
        isCallable = true;
    }

    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsType* clone() override;
    ~LgsFuncType() override = default;
};

#endif //LGSFUNCSIGNATURE_H
