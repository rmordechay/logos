#ifndef LOGOSCONSTRUCTOREXPR_H
#define LOGOSCONSTRUCTOREXPR_H
#include "LogosUnaryExpr.h"
#include "object/LogosObject.h"


class LogosConstructorExpr final : public LogosUnaryExpr {
public:
    LogosObject* object;
    explicit LogosConstructorExpr(LogosObject* logosObject) : object(logosObject) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosConstructorExpr() override = default;
};



#endif //LOGOSCONSTRUCTOREXPR_H
