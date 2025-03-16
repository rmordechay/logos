#ifndef LGSCHAR_H
#define LGSCHAR_H
#include "LgsBool.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"
#include <LogosUnaryExpr.h>

class LgsChar final : public LgsType {
public:
    string name = "Char";
    Type* IRType = Type::getInt8Ty(context);
    LgsMethodImpl isAscii = LgsMethodImpl("isAscii", &LOGOS_BOOL, name, {new LgsParam("char", this)});

    LgsChar() {
        methods[isAscii.name] = &isAscii;
    }

    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsChar() override = default;
};

inline LgsChar LOGOS_CHAR;

#endif //LGSCHAR_H
