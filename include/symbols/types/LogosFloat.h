#ifndef LOGOSFLOAT_H
#define LOGOSFLOAT_H
#include "LogosValue.h"
#include "LogosType.h"


class LogosFloat final : public LogosType {
public:
    Type* IRType = Type::getFloatTy(context);
     string typeName = "Float";

    const string name() const override;
    Type* getIRType() override;
    bool operator==(LogosType* other) const override;
    ~LogosFloat() override = default;
};

inline const string LogosFloat::name() const {
    return typeName;
}

inline Type* LogosFloat::getIRType() {
    return IRType;
}

inline bool LogosFloat::operator==(LogosType* other) const { return true;
}


#endif //LOGOSFLOAT_H
