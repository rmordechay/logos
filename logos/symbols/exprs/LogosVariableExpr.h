#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"

class LogosVariable final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariable(const std::string& name, LogosType* variableType) : LogosUnaryExpr(variableType), name(name) {}
    explicit LogosVariable(const std::string& name) : LogosVariable(name, nullptr) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    ~LogosVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
