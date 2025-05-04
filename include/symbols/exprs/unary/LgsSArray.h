#ifndef LGSSARRAY_H
#define LGSSARRAY_H
#include "LgsUnaryExpr.h"
#include "types/LgsArrayType.h"

class LgsSArray final : public LgsUnaryExpr {
public:
    LgsArrayType arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsSArray(LgsType* underlyingType, const vector<LgsExpr*>& initialElements = {}) : initialElements(initialElements) {
        arrType.sizes.emplace_back(initialElements.size());
        arrType.underlyingType = underlyingType;
        arrType.isStatic = true;
        type = &arrType;
    }
    size_t length() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsSArray() override = default;
};

#endif //LGSSARRAY_H
