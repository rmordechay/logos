#ifndef STOREEXPR_H
#define STOREEXPR_H
#include "CodeNode.h"
#include "exprs/LogosExpr.h"

#include <string>
#include <llvm/IR/IRBuilder.h>

class StoreExpr final : public CodeNode {
public:
    std::string name;
    LogosExpr *expr;

    StoreExpr(const std::string& name, LogosExpr* expr) : name(name), expr(expr) {}
    void generateCode(IRBuilder<>& builder, Module* module, std::map<std::string, Function*> functions) override;
};



#endif //STOREEXPR_H
