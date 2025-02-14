#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LogosStmt.h"

class LogosExpr;
class LogosType;

class LogosFieldAssignment final : public LogosStmt {
public:
    vector<string> names;
    LogosExpr* expr = nullptr;

    LogosFieldAssignment(const vector<string>& names, LogosExpr* expr) : names(names), expr(expr) {}
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosFieldAssignment() override = default;
};

#endif //LOGOSFIELDDEC_H
