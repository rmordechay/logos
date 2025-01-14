#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "LogosUnaryExpr.h"
#include "types/LogosType.h"
#include "types/LogosString.h"
#include "exprs/LogosExpr.h"

using namespace std;

class LogosConstantExpr final : public LogosUnaryExpr {
public:
    using Value = variant<bool, int, float, string>;
    Value value;

    template <typename T>
    explicit LogosConstantExpr(const LogosType& exprType, T value) : LogosUnaryExpr(exprType), value(value) {
        static_assert(is_same_v<T, bool> || is_same_v<T, int> || is_same_v<T, float> || is_same_v<T, string>);
    }
};

#endif //LOGOSCONSTANTEXPR_H
