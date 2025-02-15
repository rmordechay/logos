#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "LogosUnaryExpr.h"

using namespace std;

class LogosConstant final : public LogosUnaryExpr {
public:

    using ConstValue = variant<bool, int, float, string>;
    ConstValue value;

    template <typename T>
    explicit LogosConstant(LogosType* exprType, T v) : LogosUnaryExpr(exprType), value(v) {
        static_assert(is_same_v<T, bool> || is_same_v<T, int> || is_same_v<T, float> || is_same_v<T, string>);
    }

    string getName() override;
    LogosSymbolType getSymbolType() override;
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    LogosConstant* asConstant() override;
    ~LogosConstant() override = default;
};

#endif //LOGOSCONSTANTEXPR_H
