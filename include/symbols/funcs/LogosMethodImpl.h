#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LogosFunc.h"

class LogosMethodImpl final : public LogosFunc {
public:
    string parentName;
    string combinedName = parentName + "_" + name;

    LogosMethodImpl(const string& name, LogosType* funcType, const string& parentName) : LogosFunc(name, funcType), parentName(parentName) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Value* callFunc(CodeGenMetadata* metadata);
    FunctionType* getMethodType(Type* structType) const;
    ~LogosMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
