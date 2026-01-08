#pragma once
#include "LgsType.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsFuncType.h"

class LgsForeachLoop;
class LgsCgModule;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

#define ADD_FUNC "add"
#define MAP_FUNC "map"
#define FILTER_FUNC "filter"
#define FOREACH_FUNC "forEach"
#define LEN_FUNC "len"
#define IS_EMPTY_FUNC "isEmpty"
#define NOT_EMPTY_FUNC "isNotEmpty"

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    LgsExpr* size = nullptr;
    bool isStatic = false;

    explicit LgsIterable(LgsType* baseType = nullptr, LgsExpr* size = nullptr) : baseType(baseType), size(size) {}
    LgsFunc* getMethod(const std::string& methodName) override;
    size_t getDimension() const;
    virtual LgsType* getIndexType();
    virtual LgsType* getValueType();
    virtual std::string getBaseName() = 0;
    virtual bool inferBaseType(std::vector<LgsExpr*>& args) = 0;
    virtual Value* lenIR(LgsCgModule& cg, Value* iterable) = 0;
    virtual Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) = 0;
    virtual Value* getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) = 0;
    virtual bool unpackLoopVars(LgsForeachLoop* loop) const;
    virtual void setLoopIRVars(LgsCgModule& cg, LgsForeachLoop* loop);
    virtual void addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value);
    ~LgsIterable() override;
};
