#pragma once
#include "LgsType.h"
#include "utils/LgsUtils.h"

class LgsLLVMGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    virtual LgsType* getIndexType() = 0;
    virtual Value* loadWithIndex(LgsLLVMGen* cg);
    virtual uint16_t getUnpackCount() const = 0;
    virtual Value* IRLength(LgsLLVMGen& cg, LgsExpr* iterable) = 0;
    virtual Value* IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) = 0;
    virtual Value* IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) = 0;
    ~LgsIterable() override;
};

inline Value* LgsIterable::loadWithIndex(LgsLLVMGen* cg) {
    assert(0);
}

inline LgsIterable::~LgsIterable() {
    if (sizeExpr) {
        freeExpr(sizeExpr);
        sizeExpr = nullptr;
    }
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
