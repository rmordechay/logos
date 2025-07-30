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
    virtual Value* getLength(LgsCodeGen* codeGen, LgsExpr* expr) = 0;
    virtual Value* getLoopLength(LgsCodeGen* codeGen, LgsExpr* expr) = 0;
    virtual Value* isEmpty(LgsCodeGen* codeGen, LgsExpr* expr) = 0;
    virtual Value* isNotEmpty(LgsCodeGen* codeGen, LgsExpr* expr) = 0;
    ~LgsIterable() override = default;
};
