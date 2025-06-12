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
    bool isStatic = false;
    uint8_t unpackLength = 0;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    virtual Value* getLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs) = 0;
    ~LgsIterable() override = default;
};
