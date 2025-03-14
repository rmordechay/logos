#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsBool.h"
#include "LgsType.h"
#include "LgsValue.h"
#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"

#include <string>

class LgsString final : public LgsType {
public:
    Type* IRType = PointerType::get(Type::getInt8Ty(context), 0);
    string typeName = "Str";
    LgsMethodImpl isAscii = LgsMethodImpl("isAscii", &LOGOS_BOOL, typeName, {new LgsParam("str", this)});

    LgsString() {
        methods[isAscii.name] = &isAscii;
    }

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsString() override = default;
};

inline LgsString LOGOS_STRING;

#endif // LOGOSSTRING_H
