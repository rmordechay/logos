#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"
#include "LogosValue.h"

#include <string>

class LogosStr final : public LogosType {
public:
    Type* IRType = PointerType::get(Type::getInt8Ty(context), 0);
    string typeName = "Str";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    LogosField* getField(const string& name) override;
    LogosMethodImpl* getMethod(const string& name) override;
    bool equals(LogosType* other) const override;
    ~LogosStr() override = default;
};

inline LogosStr LOGOS_STRING;

#endif // LOGOSSTRING_H
