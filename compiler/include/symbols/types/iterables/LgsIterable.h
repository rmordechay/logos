#pragma once
#include "LgsType.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsFuncType.h"

class LgsForeachLoop;
class LgsCgModule;
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
    size_t getDimension() const;
    virtual LgsType* getIndexType();
    virtual LgsType* getValueType();
    virtual std::string getBaseName() = 0;
    virtual bool inferBaseType(std::vector<LgsExpr*>& args) = 0;
    virtual bool unpackLoopVars(LgsForeachLoop* loop) const;
    virtual void setLoopIRVars(LgsCgModule& cg, LgsForeachLoop* loop);

    virtual Value* lenIR(LgsCgModule& cg, Value* iterable) = 0;
    virtual Value* inIR(LgsCgModule& cg, Value* iterable, Value* value) = 0;
    virtual Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) = 0;
    virtual void addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value);
    ~LgsIterable() override;
};
