#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosType.h"
#include "LogosValue.h"

#include <string>

class LogosString final : public LogosType {
public:
    Type* IRType = PointerType::get(Type::getInt8Ty(context), 0);
    string typeName = "Str";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosString() override = default;
};

inline const string LogosString::getName() const {
    return typeName;
}

inline Type* LogosString::getIRType() {
    return IRType;
}

inline LogosConstant* LogosString::getZeroValue() {
    return new LogosConstant(this, 0);
}

inline bool LogosString::equals(LogosType* other) const {
    return typeName == other->getName();
}

inline LogosString LOGOS_STRING;

#endif // LOGOSSTRING_H
