#pragma once
#include "LgsType.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsFuncType.h"

class LgsForeachLoop;
class LgsCodeGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

#define GET_FUNC "get"
#define ADD_FUNC "add"
#define CONTAINS_FUNC "contains"
#define EQUAL_FUNC "equals"
#define LEN_FUNC "len"
#define IS_EMPTY_FUNC "isEmpty"
#define NOT_EMPTY_FUNC "isNotEmpty"
#define FIRST_ELEMENT_FUNC "first"
#define LAST_ELEMENT_FUNC "last"
#define MAP_FUNC "map"
#define FILTER_FUNC "filter"
#define FOREACH_FUNC "forEach"

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    bool isStatic = false;

    explicit LgsIterable(LgsType* baseType = nullptr) : baseType(baseType) {}
    LgsFunc* getMethod(const std::string& methodName) override;
    LgsType* getBaseType() const;
    virtual std::optional<int64_t> getConstLength();
    virtual LgsType* getIndexType();
    virtual LgsType* getValueType();
    virtual bool unpackLoopVars(LgsForeachLoop* loop) const;
    virtual void setLoopIRVars(LgsCodeGen& cg, LgsForeachLoop* loop);
    virtual bool inferBaseType(std::vector<LgsExpr*>& args) = 0;

    virtual Value* lenIR(LgsCodeGen& cg, Value* iterable) = 0;
    virtual Value* inIR(LgsCodeGen& cg, Value* iterable, Value* value) = 0;
    virtual Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) = 0;
    virtual void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value);
    ~LgsIterable() override;
};
