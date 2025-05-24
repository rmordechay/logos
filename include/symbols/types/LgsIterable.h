#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

class LgsIndex;
struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    bool isStatic = false;
    uint16_t unpackLength{};
    vector<LgsExpr*> dimsExprs;

    explicit LgsIterable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType() override;
    LgsType* inferTypeFromIter(const vector<LgsExpr*>& exprs) const;
    virtual int getDims();
    virtual LgsType* getBaseType();
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs);
    virtual Value* getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* iPtr);
    virtual Value* getLength(CodeGenMetadata* metadata, Value* arr);
    virtual LgsType* createInnerType(size_t indexRange, LgsIndex* index) const = 0;
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
