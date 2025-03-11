#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LogosType.h"
#include "constants/LogosConstant.h"


class LogosInt final : public LogosType {
public:
    Type* IRType = Type::getInt32Ty(context);
    string typeName = "Int";
    LogosConstant zeroValue = LogosConstant(this, 0);

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    LogosField* getField(const string& name) override;
    LogosMethodImpl* getMethod(const string& name) override;
    bool equals(LogosType* other) const override;
    ~LogosInt() override = default;
};

inline LogosInt LOGOS_INT;

#endif //LOGOSINT_H
