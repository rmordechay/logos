#pragma once
#include "LgsType.h"

class LgsRuntime;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    bool isStatic = false;
    uint16_t unpackLength = 0;
    size_t constSize = 0;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType() override;
    virtual LgsType* getBaseType();
    virtual Value* getLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs);
    ~LgsIterable() override = default;
};
