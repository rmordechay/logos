#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LogosFunc.h"

class LogosMethodImpl final : public LogosFunc {
public:
    string parentName;

    LogosMethodImpl(const string& name, LogosType* funcType, const string& parentName) : LogosFunc(name, funcType), parentName(parentName) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setCombinedName();
    ~LogosMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
