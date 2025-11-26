#pragma once
#include "LgsType.h"
#include "funcs/LgsFunc.h"
#include "types/LgsFuncType.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsSize.h"

class LgsForeachLoop;
class LgsLLVMGen;
class LgsVarDec;
struct LgsIndex;
struct CodegenMetadata;

#define ADD_FUNC_NAME "add"
#define MAP_FUNC_NAME "map"
#define FILTER_FUNC_NAME "filter"
#define FOREACH_FUNC_NAME "forEach"

class LgsIterable : public LgsType {
public:
    LgsType* baseType;
    LgsExpr* size = nullptr;
    bool isStatic = false;
    LgsFunc* lenFunc;
    LgsFunc* isEmptyFunc;
    LgsFunc* isNotEmptyFunc;
    LgsFunc* mapFunc;
    LgsFunc* filterFunc;

    explicit LgsIterable(LgsType* baseType = nullptr, LgsExpr* size = nullptr) : baseType(baseType), size(size) {
        lenFunc = new LgsFunc("len", &LGS_SIZE, {this}, BUILTIN | PUBLIC | METHOD);
        isEmptyFunc = new LgsFunc("isEmpty", &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);
        isNotEmptyFunc = new LgsFunc("isNotEmpty", &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);
        mapFunc = new LgsFunc(MAP_FUNC_NAME, this, {this, new LgsFuncType(baseType, {LgsParam(baseType)})}, BUILTIN | PUBLIC | METHOD);
        filterFunc = new LgsFunc(FILTER_FUNC_NAME, this, {this, new LgsFuncType(&LGS_BOOL, {LgsParam(baseType)})}, BUILTIN | PUBLIC | METHOD);
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
        addMethod(mapFunc);
        addMethod(filterFunc);
    }
    size_t getDimension() const;
    virtual LgsType* getIndexType();
    virtual LgsType* getValueType();
    virtual bool unpackLoopVarsTypes(LgsForeachLoop* loop) const;
    virtual void unpackLoopIR(LgsLLVMGen& cg, LgsForeachLoop* loop) const;
    virtual bool inferBaseType(const std::vector<LgsExpr*>& args) = 0;
    virtual Value* lenIR(LgsLLVMGen& cg, Value* iterable) = 0;
    virtual Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) = 0;
    virtual Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) = 0;
    ~LgsIterable() override;
};
