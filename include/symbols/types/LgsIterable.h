#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "LgsType.h"

struct CodeGenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    bool isStatic = false;
    vector<LgsExpr*> sizeExprs;

    explicit LgsIterable(LgsType* baseType) : baseType(baseType) {}
    LgsType* inferTypeFromIter(const vector<LgsExpr*>& exprs) const;
    virtual LgsType* getBaseType();
    virtual Value* IRLength(CodeGenMetadata* metadata);
    ~LgsIterable() override = default;
};

#endif //LOGOSITERABLE_H
