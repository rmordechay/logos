#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LgsStmt.h"
#include "exprs/unary/LgsSelection.h"

class LgsExpr;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lvalue;
    LgsExpr* rvalue;

    void createIRStmt(CodeGenMetadata* metadata) override;
    ~LgsAssignment() override;
};

#endif //LOGOSFIELDDEC_H
