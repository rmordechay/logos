#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LogosFunc.h"

class LogosMethodImpl final : public LogosFunc {
public:
    LogosObject* parentObj;

    LogosMethodImpl(const string& name, LogosType* funcType, LogosObject* obj) : LogosFunc(name, funcType), parentObj(obj) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setCombinedName();
    ~LogosMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
