#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LgsBool.h"
#include "LgsType.h"
#include "LgsVoid.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";
    Type* IRType = Type::getInt32Ty(context);

    LgsMethodImpl isOdd = LgsMethodImpl("isOdd", &LOGOS_BOOL, name, {new LgsParam("n", this)});
    LgsMethodImpl isEven = LgsMethodImpl("isEven", &LOGOS_BOOL, name, {new LgsParam("n", this)});

    LgsInt() {
        methods[isOdd.name] = &isOdd;
        methods[isEven.name] = &isOdd;
    }

    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsInt() override = default;
};

inline LgsInt LOGOS_INT;

#endif //LOGOSINT_H
