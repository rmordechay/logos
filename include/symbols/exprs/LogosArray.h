#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LogosIterable.h"
#include "LogosUnaryExpr.h"
#include "exprs/LogosExpr.h"

class LogosArray final : public LogosUnaryExpr, public LogosIterable {
public:
    vector<LogosExpr*> elements;

    explicit LogosArray() : LogosUnaryExpr(nullptr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    ~LogosArray() override = default;
};

#endif //LOGOSARRAY_H
