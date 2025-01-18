#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include "CodeGeneration.h"
#include "exprs/LogosExpr.h"

class LogosStmt : public CodeGeneration {
public:
    ~LogosStmt() override = default;
};

#endif //LOGOSSTMT_H
