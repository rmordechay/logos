#ifndef LGSCHAR_H
#define LGSCHAR_H
#include "LgsBool.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"
#include <LogosUnaryExpr.h>

class LgsChar final : public LgsType {
public:
    string typeName = "Char";
    Type* IRType = Type::getInt8Ty(context);
    LgsMethodImpl isAscii = LgsMethodImpl("isAscii", &LOGOS_BOOL, typeName, {new LgsParam("char", this)});

    LgsChar() {
        methods[isAscii.name] = &isAscii;
    }

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
};



#endif //LGSCHAR_H
