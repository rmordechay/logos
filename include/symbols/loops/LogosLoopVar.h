#ifndef LOGOSLOOPVAR_H
#define LOGOSLOOPVAR_H
#include <LogosValue.h>


class LogosType;

class LogosLoopVar final: public LogosValue {
public:
    string name;
    LogosType* type = nullptr;
    LogosExpr* expr = nullptr;

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosLoopVar() override = default;
};



#endif //LOGOSLOOPVAR_H
