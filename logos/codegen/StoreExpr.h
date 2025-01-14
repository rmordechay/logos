#ifndef STOREEXPR_H
#define STOREEXPR_H
#include "CodeNode.h"
#include "RuntimeScope.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosExpr.h"


class StoreExpr final : public CodeNode {
public:
    const string name;
    LogosExpr* expr;

    StoreExpr(const std::string& name, LogosExpr* logosExpr) : name(name), expr(logosExpr) {}
    Value* getUnary(LogosUnaryExpr* unary) const;
    Value* getBinary(const LogosBinaryExpr* binary);
    Value* getExpr(LogosExpr* expr);
    void generateProlog(RuntimeScope* scope) override;
    void generateEpilog(RuntimeScope* scope) override;
    ~StoreExpr() override = default;
};



#endif //STOREEXPR_H
