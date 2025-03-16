#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "unary/LogosUnaryExpr.h"

class LgsFloatConst;
class LgsBool;
class LgsIntConst;
class LgsStrConst;
using namespace std;

class LgsConst : public LgsUnaryExpr {
public:
    explicit LgsConst(LgsType* type) : LgsUnaryExpr(type) {}
    ~LgsConst() override = default;
};


#endif //LOGOSCONSTANTEXPR_H
