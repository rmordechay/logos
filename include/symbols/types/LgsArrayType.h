#ifndef LOGOSARRAYTYPE_H
#define LOGOSARRAYTYPE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsArrayType final : public LgsType {
public:
    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsArrayType() override = default;
};

inline const string LgsArrayType::getName() const {
    return "";
}

inline Type* LgsArrayType::getIRType() {
    assert(false && "not implemented");
}

inline LgsConst* LgsArrayType::getZeroValue() {
    assert(false && "not implemented");
}

inline bool LgsArrayType::equals(LgsType* other) const {
    assert(false && "not implemented");
}

inline LgsType* LgsArrayType::inferBinaryType(LgsType* other) {
    assert(false && "not implemented");
}

#endif //LOGOSARRAYTYPE_H
