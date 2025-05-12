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
    FunctionType* IRFuncType = nullptr;
    bool isMethod = false;
    bool isStatic = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool hasDefaultParams = false;

    string getAsStr() const;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    bool equals(const LgsFuncCall* other) const;
    bool equalsVariadic(const LgsFuncCall* funcCall) const;
    bool equalsDefaultParams(const LgsFuncCall* funcCall) const;
    static string getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames);
    ~LgsFuncType() override = default;
};


#endif //LGSFUNCSIGNATURE_H
