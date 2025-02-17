#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LogosUnaryExpr.h"

#include <LogosValue.h>


class LogosArrayIndex final : public LogosUnaryExpr {
public:
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    LogosSymbolType getSymbolType() override;
    string getName() override;
    ~LogosArrayIndex() override = default;
};



#endif //LOGOSARRAYINDEX_H
