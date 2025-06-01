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
    LgsType* getIterType(const LgsIndex* index) const;
    virtual LgsType* getBaseType();
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs);
    virtual Value* getElement(Module* module, Value* iterPtr, Value* iPtr);
    virtual Value* getLength(Module* module, Value* iterValue);
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
