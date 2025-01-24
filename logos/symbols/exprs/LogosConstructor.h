#ifndef LOGOSCONSTRUCTOREXPR_H
#define LOGOSCONSTRUCTOREXPR_H
#include "LogosUnaryExpr.h"
#include "object/LogosObject.h"


class LogosConstructor final : public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;

    explicit LogosConstructor(const string& name) : name(name) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    ~LogosConstructor() override = default;
};



#endif //LOGOSCONSTRUCTOREXPR_H
