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
    void setIRLoopVars(CodeGenMetadata* metadata) override;
    void setIRIterable(CodeGenMetadata* metadata) override;
    Value* loopStart(CodeGenMetadata* metadata) override;
    Value* loopEnd(CodeGenMetadata* metadata) override;
    ~LgsForeachLoop() override;
};

#endif //LOGOSFOREACHLOOP_H
