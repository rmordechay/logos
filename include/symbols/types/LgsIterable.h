#pragma once
#include "LgsType.h"

class LgsCodeGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    uint8_t unpackLength = 0;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    virtual LgsType* getIndexType() = 0;
    virtual LgsType* getValueType() = 0;
    virtual Value* getLength(LgsExpr* expr) = 0;
    virtual Value* getLoopLength(LgsExpr* expr) = 0;
    virtual Value* isEmpty(LgsExpr* expr) = 0;
    virtual Value* isNotEmpty(LgsExpr* expr) = 0;
    ~LgsIterable() override = default;
};
