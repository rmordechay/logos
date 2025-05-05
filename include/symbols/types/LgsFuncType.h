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
    const string getName() const override;
    bool equals(LgsType* other) const override;
    bool equals(const LgsFuncCall* other) const;
    LgsType* inferBinaryType(LgsType* other) override;
    string getAsStr(bool withType = false) const;
    void setStructRet(Function::arg_iterator& args, LgsObject* obj) const;

    virtual string getIRName();
    virtual Function* getIRFunc(const CodeGenMetadata* metadata);
    virtual FunctionType* getIRFuncType(const CodeGenMetadata* metadata);
    virtual void setIRFuncParams(Argument* IRParams);
    static string getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames);
    ~LgsFuncType() override;
};


#endif //LGSFUNCSIGNATURE_H
