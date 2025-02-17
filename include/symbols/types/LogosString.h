#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LogosValue.h"
#include "LogosType.h"

#include <string>


class LogosString final : public LogosType {
public:
    Type* IRType = nullptr;
     string typeName = "Str";

    const string name() const override;
    Type* getIRType() override;
    bool operator==(LogosType* other) const override;
    ~LogosString() override = default;
};

inline const string LogosString::name() const {
    return typeName;
}

inline Type* LogosString::getIRType() {
    if (IRType) return IRType;
    return nullptr;
}

inline bool LogosString::operator==(LogosType* other) const { return true;
}

#endif //LOGOSSTRING_H
