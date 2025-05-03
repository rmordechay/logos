#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "funcs/LgsParam.h"
#include "LgsType.h"

class LgsParam;

class LgsFuncType : public LgsType {
public:
    string name;
    string IRName;
    LgsType* type;
    vector<LgsParam> params;
    bool hasDefaultParams = false;
    FunctionType* IRFuncType = nullptr;

    LgsFuncType(const string& name, LgsType* type, const vector<LgsParam>& params = {}) : name(name), type(type), params(params) {}
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    const string getName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getAsStr(bool withType = false) const;
    void setStructRet(Function::arg_iterator& args, LgsObject* obj) const;

    virtual string getIRName();
    virtual Function* getIRFunc(const CodeGenMetadata* metadata);
    virtual FunctionType* getIRFuncType(const CodeGenMetadata* metadata);
    virtual void setIRFuncParams(Argument* IRParams);
    static string getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames);
    ~LgsFuncType() override = default;
};

class LgsMethodType final : public LgsFuncType {
public:
    string parentName;

    LgsMethodType(const string& name, LgsType* type, const vector<LgsParam>& params): LgsFuncType(name, type, params) {}
    string getIRName() override;
    FunctionType* getIRFuncType(const CodeGenMetadata* metadata) override;
    void setIRFuncParams(Argument* args) override;
    bool equals(LgsType* other) const override;
    ~LgsMethodType() override = default;
};


#endif //LGSFUNCSIGNATURE_H
