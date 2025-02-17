#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LogosStmt.h"

class LogosExpr;
class LogosType;

class LogosFieldDefinition final : public LogosStmt {
public:
    int position = -1;
    vector<string> names;
    LogosExpr* expr = nullptr;

    LogosFieldDefinition(const vector<string>& names, LogosExpr* expr) : names(names), expr(expr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosFieldDefinition() override;
};

#endif //LOGOSFIELDDEC_H
