#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    bool isStatic = false;
    uint16_t unpackLength = 0;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType() override;
    virtual LgsType* getBaseType();
    virtual Value* getLength(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) = 0;
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs);
    virtual Value* getElement(LgsRuntime* runtime, Value* iterPtr, Value* iPtr);
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
