#pragma once
#include "LgsType.h"

class LgsRuntime;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    size_t iterLen = 0;
    uint8_t unpackLength = 0;
    bool isStatic = false;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    size_t getIterBytesSize(size_t n) const;
    virtual LgsType* getIndexType() = 0;
    virtual LgsType* getValueType() = 0;
    virtual Value* getLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* isEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* isNotEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    ~LgsIterable() override = default;
};

inline size_t LgsIterable::getIterBytesSize(const size_t n) const {
    return dataLayout.getTypeAllocSize(baseType->getIRType()).getFixedValue() * n;
}
