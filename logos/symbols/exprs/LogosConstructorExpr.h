#ifndef LOGOSCONSTRUCTOREXPR_H
#define LOGOSCONSTRUCTOREXPR_H
#include "LogosUnaryExpr.h"
#include "object/LogosObject.h"


class LogosConstructorExpr final : public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;

    explicit LogosConstructorExpr(const string& name) : name(name) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosConstructorExpr() override = default;
};



#endif //LOGOSCONSTRUCTOREXPR_H
