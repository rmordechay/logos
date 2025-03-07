#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LogosFunc.h"

class LogosMethodImpl final : public LogosFunc {
public:
    LogosObject* obj;
    string combinedName;

    LogosMethodImpl(const string& name, LogosType* funcType, LogosObject* obj) : LogosFunc(name, funcType), obj(obj) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Function* getIRFunc(CodeGenMetadata* metadata);
    ~LogosMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
