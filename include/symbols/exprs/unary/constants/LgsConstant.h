#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include <LogosMetadata.h>
#include "unary/LogosUnaryExpr.h"
#include <variant>

class LgsFloatConst;
class LgsBool;
class LgsIntConst;
class LgsStrConst;
using namespace std;

class LgsConstant : public LgsUnaryExpr {
public:
    explicit LgsConstant(LgsType* type) : LgsUnaryExpr(type) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsConstant() override = default;
};


#endif //LOGOSCONSTANTEXPR_H
