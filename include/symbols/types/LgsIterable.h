#pragma once
#include "LgsType.h"

class LgsModule;
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
    virtual LgsType* getIndexType() = 0;
    virtual LgsType* getValueType() = 0;
    virtual Value* getLength(LgsModule* module, LgsExpr* expr) = 0;
    virtual Value* getLoopLength(LgsModule* module, LgsExpr* expr) = 0;
    virtual Value* isEmpty(LgsModule* module, LgsExpr* expr) = 0;
    virtual Value* isNotEmpty(LgsModule* module, LgsExpr* expr) = 0;
    ~LgsIterable() override = default;
};