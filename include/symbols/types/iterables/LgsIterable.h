#pragma once
#include "LgsType.h"
#include "utils/LgsUtils.h"

class LgsForeachLoop;
class LgsLLVMGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

#define ADD_FUNC_NAME "add"
#define LEN_FUNC_NAME "len"
#define IS_EMPTY_FUNC_NAME "isEmpty"
#define IS_NOT_EMPTY_FUNC_NAME "isNotEmpty"
#define MAP_FUNC_NAME "map"
#define FILTER_FUNC_NAME "filter"
#define FOREACH_FUNC_NAME "forEach"

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

    virtual LgsFunc* getLenFunc();
    virtual LgsFunc* getIsEmptyFunc();
    virtual LgsFunc* getIsNotEmptyFunc();
    virtual LgsFunc* getAddFunc();
    virtual LgsFunc* getMapFunc();
    virtual LgsFunc* getFilterFunc();
    virtual LgsType* getIndexType();
    virtual LgsType* getValueType();
    virtual bool unpackLoopVarsTypes(LgsForeachLoop* loop) const;
    virtual void unpackLoopVarsIR(LgsLLVMGen& cg, std::vector<LgsVarDec*> varDecs, Value* iterPtr, Value* index) const;
    virtual Value* lengthIR(LgsLLVMGen& cg, Value* iterable) = 0;
    virtual Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) = 0;
    virtual Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index);
    ~LgsIterable() override;
};
