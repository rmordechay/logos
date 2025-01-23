#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "../LogosStack.h"
#include "LogosUnaryExpr.h"

class LogosVariable final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariable(const std::string& name, const LogosType* variableType) : LogosUnaryExpr(variableType), name(name) {}
    explicit LogosVariable(const std::string& name) : LogosVariable(name, nullptr) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
