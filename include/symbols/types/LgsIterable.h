#pragma once
#include "LgsType.h"
#include "utils/LgsUtils.h"

class LgsCodeGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    virtual LgsType* getIndexType() = 0;
    virtual uint16_t getUnpackCount() const = 0;
    virtual Value* IRLength(LgsCodeGen& codeGen, LgsExpr* iterable) = 0;
    virtual Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) = 0;
    virtual Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) = 0;
    ~LgsIterable() override;
};

inline LgsIterable::~LgsIterable() {
    if (sizeExpr) {
        delete sizeExpr;
        sizeExpr = nullptr;
    }
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
