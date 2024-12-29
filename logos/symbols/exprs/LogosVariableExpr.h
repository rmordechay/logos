#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"

#include <string>

class LogosVariableExpr final : public LogosUnaryExpr {
public:
    std::string name;
    const std::shared_ptr<LogosType> logosType;

    explicit LogosVariableExpr(const std::string& name) : name(name) {}
    std::shared_ptr<LogosType> value() const override { return logosType; }
};

#endif //LOGOSVARIABLEEXPR_H
