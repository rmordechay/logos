#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LogosFunc.h"

class LogosMethodImpl final : public LogosFunc {
public:
    string objName;
    string combinedName = objName + "_" + name;

    LogosMethodImpl(const string& name, LogosType* funcType, const string& objName) : LogosFunc(name, funcType), objName(objName) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Value* callFunc(CodeGenMetadata* metadata);
    Function* getIRFunc(CodeGenMetadata* metadata);
    ~LogosMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
