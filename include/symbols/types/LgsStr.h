#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsType.h"
#include "funcs/LgsMethodImpl.h"

#include <string>

class LgsStr final : public LgsType {
public:
    string typeName = "Str";
    Type* IRType = PointerType::get(Type::getInt8Ty(context), 0);

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsStr() override = default;
};

inline LgsStr LOGOS_STRING;

#endif // LOGOSSTRING_H
