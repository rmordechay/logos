#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LgsStmt.h"

class LgsExpr;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lvalue;
    LgsExpr* rvalue;

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsAssignment() override;
};

#endif //LOGOSFIELDDEC_H
