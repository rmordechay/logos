#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LogosFunc.h"
#include "StackFrame.h"
#include "types/LogosInt.h"

class LogosPrint final : public LogosFunc {
public:
    static constexpr auto name = "print";

    LogosPrint() : LogosFunc(name, LOGOS_INT) {}
    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    ~LogosPrint() override = default;
};

inline const LogosFunc& LOGOS_PRINT = LogosPrint();

#endif //LOGOSPRINT_H
