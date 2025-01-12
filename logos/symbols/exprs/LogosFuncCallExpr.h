#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "funcs/LogosFunc.h"

class LogosFuncCallExpr final : public LogosUnaryExpr {
public:
    LogosFuncCallExpr(const LogosType* exprType, const std::string& name, LogosFunc* func,
        const std::vector<LogosExpr*>& args, const LogosType* logosType) :
        LogosUnaryExpr(exprType),
        name(name),
        func(func),
        args(args),
        logosType(logosType) {
    }

    const std::string name;
    const LogosFunc* func;
    std::vector<LogosExpr*> args;
    const LogosType* logosType;
};

#endif //LOGOSFUNCCALLEXPR_H
