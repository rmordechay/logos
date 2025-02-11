#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"

class LogosExpr: public CodeGeneration {
public:
    LogosType* type = nullptr;

    explicit LogosExpr(LogosType* type) : type(type) {}
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

