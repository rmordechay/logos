#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "funcs/LogosFunc.h"

class LogosFuncCallExpr final : public LogosUnaryExpr {
public:
    std::string name;
    std::shared_ptr<LogosFunc> func;
    std::vector<std::shared_ptr<LogosExpr>> args;
    const std::shared_ptr<LogosType> logosType;

    explicit LogosFuncCallExpr(const std::string& name, const std::shared_ptr<LogosFunc>& func) : LogosUnaryExpr(), name(name), func(func) {}
    std::shared_ptr<LogosType> value() const override { return logosType; }
};

#endif //LOGOSFUNCCALLEXPR_H
