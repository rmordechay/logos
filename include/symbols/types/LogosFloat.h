#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosType.h"
#include "constants/LogosConstant.h"

class LogosFloat final : public LogosType {
public:
    Type* IRType = Type::getFloatTy(context);
    string typeName = "Float";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    LogosField* getField(const string& name) override;
    LogosMethodImpl* getMethod(const string& name) override;
    bool equals(LogosType* other) const override;
    ~LogosFloat() override = default;
};

inline LogosFloat LOGOS_FLOAT;

#endif // LOGOSFLOAT_H
