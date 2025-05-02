#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    vector<size_t> iterableSize;
    LgsType* underlyingType;

    explicit LgsIterable(LgsType* underlyingType, const vector<size_t>& iterableSize = {}) : iterableSize(iterableSize), underlyingType(underlyingType) {}
    virtual Type* getUnderlyingIRType() = 0;
    bool isIterable() override;
    ~LgsIterable() override = default;
};

inline bool LgsIterable::isIterable() {
    return true;
}

#endif //LOGOSITERABLE_H
