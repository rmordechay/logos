#ifndef LOGOSLOOPVAR_H
#define LOGOSLOOPVAR_H
#include <LogosValue.h>

class LogosType;

class LogosLoopVar final: public LogosValue {
public:
    string name;
    LogosType* type = nullptr;
    LogosExpr* expr = nullptr;

    explicit LogosLoopVar(const string& name) : name(name) {}
    explicit LogosLoopVar(const string& name, LogosType* type) : name(name), type(type) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosLoopVar() override;
};



#endif //LOGOSLOOPVAR_H
