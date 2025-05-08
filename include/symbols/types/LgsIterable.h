#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* underlyingType;
    bool isStaticIter = false;
    vector<size_t> sizes;

    explicit LgsIterable(LgsType* underlyingType) : underlyingType(underlyingType) {}
    size_t getDims() const;
    bool isIterable() override;
    virtual LgsType* getUnderlyingType();
    virtual Value* IRLength(CodeGenMetadata* metadata);
    LgsType* inferTypeFromIter(const vector<LgsExpr*>& exprs) const;
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
