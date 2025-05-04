#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    vector<size_t> sizes;
    LgsType* underlyingType;

    explicit LgsIterable(LgsType* underlyingType, const vector<size_t>& iterableSize = {}) : sizes(iterableSize), underlyingType(underlyingType) {}
    LgsType* getUnderlyingType() override;
    bool isIterable() override;
    ~LgsIterable() override = default;
};

inline LgsType* LgsIterable::getUnderlyingType() {
    return underlyingType;
}

inline bool LgsIterable::isIterable() {
    return true;
}

#endif //LOGOSITERABLE_H
