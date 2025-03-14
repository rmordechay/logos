#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LgsBool.h"
#include "LgsType.h"
#include "LgsVoid.h"

class LgsInt final : public LgsType {
public:
    string typeName = "Int";
    Type* IRType = Type::getInt32Ty(context);

    LgsMethodImpl isOdd = LgsMethodImpl("isOdd", &LOGOS_BOOL, typeName, {new LgsParam("n", this)});
    LgsMethodImpl isEven = LgsMethodImpl("isEven", &LOGOS_BOOL, typeName, {new LgsParam("n", this)});

    LgsInt() {
        methods[isOdd.name] = &isOdd;
        methods[isEven.name] = &isOdd;
    }

    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsInt() override = default;
};

inline LgsInt LOGOS_INT;

#endif //LOGOSINT_H
