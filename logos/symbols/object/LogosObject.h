#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "exprs/LogosUnaryExpr.h"
#include "types/LogosUserType.h"

class LogosObject : public LogosUnaryExpr {
public:
    LogosUserType* type = nullptr;
    explicit LogosObject(LogosUserType* type) : type(type) {}
    ~LogosObject() = default;
};

#endif //LOGOSOBJECT_H
