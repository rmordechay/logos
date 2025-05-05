#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "funcs/LgsParam.h"
#include "LgsType.h"

class LgsParam;

class LgsFuncType : public LgsType {
public:
    string name;
    string IRName;
    LgsType* rt;
    vector<LgsParam*> params;
    bool hasDefaultParams = false;
    FunctionType* IRFuncType = nullptr;

    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    const string getPrettyName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(const LgsFuncCall* other) const;
    string getAsStr(bool withType = false) const;
    virtual string getIRName();
    static string getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames);
    ~LgsFuncType() override;
};


#endif //LGSFUNCSIGNATURE_H
