#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "LogosUnaryExpr.h"
#include "StackFrame.h"
#include "types/LogosType.h"
#include "types/LogosString.h"

using namespace std;

class LogosConstantExpr final : public LogosUnaryExpr {
public:
    using ConstValue = variant<bool, int, float, string>;
    ConstValue value;

    template <typename T>
    explicit LogosConstantExpr(const LogosType* exprType, T v) : LogosUnaryExpr(exprType), value(v) {
        static_assert(is_same_v<T, bool> || is_same_v<T, int> || is_same_v<T, float> || is_same_v<T, string>);
    }

    Value* getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) override;
    ~LogosConstantExpr() override = default;
};

#endif //LOGOSCONSTANTEXPR_H
