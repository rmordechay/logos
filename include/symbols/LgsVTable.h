#ifndef LGSVTABLE_H
#define LGSVTABLE_H
#include "exprs/unary/LgsHashMap.h"

class LgsVTable final : public LgsHashMap {
public:
    explicit LgsVTable() : LgsHashMap(new LgsStr(), &LGS_ANY) {}
    void setImplementsVFuncs(LgsRuntime* runtime, LgsObject* obj, Value* IRValue) const;
    Value* resolveVirtualFunc(LgsRuntime* runtime, LgsExpr* parent, LgsFunc* func) const;
    ~LgsVTable() override = default;
};

#endif //LGSVTABLE_H
