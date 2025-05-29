#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct LgsIndex;
struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    bool isStatic = false;
    uint16_t unpackLength = 0;
    LgsExpr* dimsExpr = nullptr;

    explicit LgsIterable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType() override;
    LgsType* getIterType(const LgsIndex* index) const;
    virtual LgsType* getBaseType();
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs);
    virtual Value* getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* iPtr);
    virtual Value* getLength(CodeGenMetadata* metadata, Value* iterValue);
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
