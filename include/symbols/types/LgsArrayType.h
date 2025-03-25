#ifndef LOGOSARRAYTYPE_H
#define LOGOSARRAYTYPE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsArrayType final : public LgsType {
public:
    LgsType* underlyingType = nullptr;

    LgsArrayType() = default;
    explicit LgsArrayType(LgsType* underlyingType) : underlyingType(underlyingType) {}
    const string getName() const override;
    Type* getIRType(int size) override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsArrayType() override = default;
};

#endif //LOGOSARRAYTYPE_H
