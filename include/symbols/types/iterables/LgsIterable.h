#pragma once
#include "LgsType.h"
#include "utils/LgsUtils.h"

class LgsLLVMGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

#define ADD_FUNC_NAME "add"
#define LEN_FUNC_NAME "len"
#define IS_EMPTY_FUNC_NAME "isEmpty"
#define IS_NOT_EMPTY_FUNC_NAME "isNotEmpty"

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    LgsExpr* sizeExpr = nullptr;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {
        addEmptyMethod(ADD_FUNC_NAME);
        addEmptyMethod(LEN_FUNC_NAME);
        addEmptyMethod(IS_EMPTY_FUNC_NAME);
        addEmptyMethod(IS_NOT_EMPTY_FUNC_NAME);
    }

    LgsFunc* getMethod(const std::string& name) override;
    virtual LgsFunc* getLenFunc();
    virtual LgsFunc* getIsEmptyFunc();
    virtual LgsFunc* getIsNotEmptyFunc();
    virtual LgsFunc* getAddFunc();
    virtual LgsFunc* getMapFunc();
    virtual LgsType* getIndexType() = 0;
    virtual Value* loadWithIndex(LgsLLVMGen* cg);
    virtual uint16_t getUnpackCount() const = 0;
    virtual Value* IRLength(LgsLLVMGen& cg, Value* iterable) = 0;
    ~LgsIterable() override;
};
