#ifndef STOREEXPR_H
#define STOREEXPR_H
#include "CodeNode.h"

class StoreExpr final : public CodeNode {
public:
    const string name;
    LogosExpr* expr;

    StoreExpr(const std::string& name, LogosExpr* logosExpr) : name(name), expr(logosExpr) {}
    void generateCode(RuntimeStackFrame* runtimeStack) override;
    ~StoreExpr() override = default;
};



#endif //STOREEXPR_H
