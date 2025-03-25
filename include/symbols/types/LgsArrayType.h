#ifndef LOGOSARRAYTYPE_H
#define LOGOSARRAYTYPE_H
#include "LgsType.h"
#include "funcs/LgsMethodImpl.h"

struct CodeGenMetadata;

class LgsArrayType final : public LgsType {
public:
    LgsType* underlyingType = nullptr;
    LgsMethodImpl arrayTypeAddFunc = LgsMethodImpl("add", nullptr, "name", {new LgsParam("n", underlyingType)});

    LgsArrayType() {
        methods[arrayTypeAddFunc.name] = {&arrayTypeAddFunc};
    }

    explicit LgsArrayType(LgsType* underlyingType) : underlyingType(underlyingType) {}
    const string getName() const override;
    Type* getIRType(int size) override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsArrayType() override = default;
};

#endif //LOGOSARRAYTYPE_H
