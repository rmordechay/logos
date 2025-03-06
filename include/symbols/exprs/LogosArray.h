#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "exprs/LogosExpr.h"

class LogosArray final : public LogosExpr {
public:
    vector<LogosExpr*> elements;

    explicit LogosArray() : LogosExpr(nullptr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosArray() override = default;
};

#endif //LOGOSARRAY_H
