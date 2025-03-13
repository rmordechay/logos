#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LogosFunc.h"

class LogosMethodImpl final : public LogosFunc {
public:
    string parentName;

    LogosMethodImpl(const string& name, LogosType* funcType, const string& parentName) : LogosFunc(name, funcType), parentName(parentName) {
        setCombinedName();
    }
    LogosMethodImpl(const string& name, LogosType* funcType, const string& parentName, const vector<LogosParam*>& params) : LogosFunc(name, funcType, params), parentName(parentName) {
        setCombinedName();
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setCombinedName();
    ~LogosMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
