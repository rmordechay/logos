#ifndef LGSSARRAY_H
#define LGSSARRAY_H
#include "../../types/LgsIterable.h"
#include "LgsUnaryExpr.h"
#include "types/LgsSArrType.h"

class LgsSArray final : public LgsUnaryExpr {
public:
    vector<size_t> arraySize;
    vector<LgsExpr*> initialElements;

    explicit LgsSArray(LgsType* underlyingType, const vector<size_t>& arraySize, const vector<LgsExpr*>& initialElements = {}) : arraySize(arraySize), initialElements(initialElements) {
        assert(!arraySize.empty());
        type = new LgsSArrType(underlyingType, arraySize);
    }
    size_t length() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsSArray() override = default;
};

#endif //LGSSARRAY_H
