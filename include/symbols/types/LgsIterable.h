#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* underlyingType;
    bool isStatic = false;
    vector<size_t> sizes;

    explicit LgsIterable(LgsType* underlyingType) : underlyingType(underlyingType) {}
    size_t getDims() const;
    bool isIterable() override;
    virtual LgsType* getUnderlyingType();
    virtual Value* IRLength(CodeGenMetadata* metadata);
    ~LgsIterable() override = default;
};

inline size_t LgsIterable::getDims() const {
    return sizes.size();
}

inline bool LgsIterable::isIterable() {
    return true;
}

inline LgsType* LgsIterable::getUnderlyingType() {
    return underlyingType;
}

inline Value* LgsIterable::IRLength(CodeGenMetadata* metadata) {
    assert(false);
}

#endif //LOGOSITERABLE_H
