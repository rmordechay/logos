#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "LogosUnaryExpr.h"
#include "funcs/LogosFunc.h"
#include <map>

class LogosFuncCallExpr final : public LogosUnaryExpr {
public:
    const std::string name;
    const LogosFunc* func;
    std::vector<LogosExpr*> args;

    LogosFuncCallExpr(const std::string& name, const LogosFunc* func, const std::vector<LogosExpr*>& args) :
        LogosUnaryExpr(func->funcType),
        name(name),
        func(func),
        args(args) {
    }

    ~LogosFuncCallExpr() = default;
};

#endif //LOGOSFUNCCALLEXPR_H
