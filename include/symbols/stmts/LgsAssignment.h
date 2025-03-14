#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LgsStmt.h"

class LogosExpr;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LogosExpr* lvalue;
    LogosExpr* rvalue;

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsAssignment() override;
};

#endif //LOGOSFIELDDEC_H
