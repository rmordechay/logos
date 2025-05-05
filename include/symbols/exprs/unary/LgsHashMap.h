#ifndef LGSHASHMAP_H
#define LGSHASHMAP_H
#include "LgsUnaryExpr.h"
#include "types/LgsMap.h"

class LgsHashMap final : public LgsUnaryExpr {
public:
    LgsMap mapType;
    map<LgsExpr*, LgsExpr*> initialElements;

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsHashMap() override = default;
};

#endif //LGSHASHMAP_H
