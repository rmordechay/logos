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
    LgsType* rt;
    vector<LgsParam*> params;
    bool isStatic = false;
    bool isPublic = false;
    bool hasDefaultParams = false;
    FunctionType* IRFuncType = nullptr;

    string getAsStr(bool withType = false) const;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    bool equals(const LgsFuncCall* other) const;
    static string getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames);
    ~LgsFuncType() override;
};


#endif //LGSFUNCSIGNATURE_H
