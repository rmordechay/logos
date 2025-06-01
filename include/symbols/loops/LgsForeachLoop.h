#ifndef LOGOSFOREACHLOOP_H
#define LOGOSFOREACHLOOP_H
#include "LgsForLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsForLoop {
public:
    LgsUnaryExpr* iterExpr = nullptr;
    Value* iterPtr = nullptr;

    explicit LgsForeachLoop(LgsUnaryExpr* iterable) : iterExpr(iterable) {}
    void setIRLoopVars(CodegenMetadata* metadata) override;
    void setIRIterable(CodegenMetadata* metadata) override;
    Value* loopStart(CodegenMetadata* metadata) override;
    Value* loopEnd(CodegenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};

#endif //LOGOSFOREACHLOOP_H
