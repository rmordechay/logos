#pragma once
#include "LgsType.h"
#include "utils/LgsUtils.h"

class LgsLLVM;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    virtual LgsType* getIndexType() = 0;
    virtual Value* loadWithIndex(LgsLLVM* codeGen);
    virtual uint16_t getUnpackCount() const = 0;
    virtual Value* IRLength(LgsLLVM& codeGen, LgsExpr* iterable) = 0;
    virtual Value* IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) = 0;
    virtual Value* IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) = 0;
    ~LgsIterable() override;
};

inline Value* LgsIterable::loadWithIndex(LgsLLVM* codeGen) {
    assert(0);
}

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
