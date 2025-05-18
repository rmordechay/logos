#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    vector<LgsExpr*> dimsExprs;
    uint16_t unpackLength = 0;

    explicit LgsIterable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType() override;
    int getExprConstNumber(LgsExpr* expr);
    LgsType* inferTypeFromIter(const vector<LgsExpr*>& exprs) const;
    virtual int getDims();
    virtual LgsType* getBaseType();
    virtual Value* IRLength(CodeGenMetadata* metadata);
    virtual void unpackTypes(const vector<LgsVarDec*>& varDecs);
    virtual LgsType* createInnerType(size_t indexRange) const = 0;
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
