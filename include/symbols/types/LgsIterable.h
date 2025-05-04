#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* underlyingType;
    bool isStatic = true;
    vector<size_t> sizes;

    explicit LgsIterable(LgsType* underlyingType) : underlyingType(underlyingType) {}
    size_t getDims() const;
    Type* getIRType() override;
    bool isIterable() override;
    ~LgsIterable() override = default;
};

inline Type* LgsIterable::getIRType() {
    if (!isStatic) return ptrTy;
    if (IRType) return IRType;
    IRType = underlyingType->getIRType();
    assert(getDims() > 0);
    for (auto size = sizes.rbegin(); size != sizes.rend(); ++size) {
        IRType = ArrayType::get(IRType, *size);
    }
    return IRType;
}

inline size_t LgsIterable::getDims() const {
    return sizes.size();
}

inline bool LgsIterable::isIterable() {
    return true;
}

#endif //LOGOSITERABLE_H
