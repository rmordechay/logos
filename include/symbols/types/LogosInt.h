#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LogosBool.h"
#include "LogosType.h"
#include "LogosVoid.h"
#include "constants/LogosConstant.h"


class LogosInt final : public LogosType {
public:
    string typeName = "Int";
    Type* IRType = Type::getInt32Ty(context);
    LogosConstant zeroValue = LogosConstant(this, 0);

    LogosMethodImpl isOdd = LogosMethodImpl("isOdd", &LOGOS_BOOL, typeName, {new LogosParam("n", this)});
    LogosMethodImpl isEven = LogosMethodImpl("isEven", &LOGOS_BOOL, typeName, {new LogosParam("n", this)});

    LogosInt() {
        methods[isOdd.name] = &isOdd;
        methods[isEven.name] = &isOdd;
    }

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
