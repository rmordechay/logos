#include "types/iterables/LgsIterable.h"

#include "exprs/LgsIterIndex.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsSize.h"

LgsFunc* LgsIterable::getMethod(const std::string& methodName) {
    if (methodName == ADD_FUNC_NAME) {
        return getAddFunc();
    }
    if (methodName == LEN_FUNC_NAME) {
        return getLenFunc();
    }
    if (methodName == IS_EMPTY_FUNC_NAME) {
        return getIsEmptyFunc();
    }
    if (methodName == IS_NOT_EMPTY_FUNC_NAME) {
        return getIsNotEmptyFunc();
    }
    if (methodName == MAP_FUNC_NAME) {
        return getMapFunc();
    }
    if (methodName == FILTER_FUNC_NAME) {
        return getFilterFunc();
    }
    if (methodName == FOREACH_FUNC_NAME) {
        assert(0);
    }
    const auto method = methods.find(methodName);
    if (method == methods.end()) return nullptr;
    assert(method->second);
    return method->second;
}

LgsFunc* LgsIterable::getAddFunc() {
    return nullptr;
}

LgsFunc* LgsIterable::getMapFunc() {
    const auto func = methods.find(MAP_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(MAP_FUNC_NAME, this, {this, new LgsFuncType(baseType, {LgsParam(baseType)})}, BUILTIN | PUBLIC | METHOD);
    methods[MAP_FUNC_NAME] = func->second;
    return func->second;
}

LgsFunc* LgsIterable::getFilterFunc() {
    const auto func = methods.find(FILTER_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(FILTER_FUNC_NAME, this, {this, new LgsFuncType(&LGS_BOOL, {LgsParam(baseType)})}, BUILTIN | PUBLIC | METHOD);
    methods[FILTER_FUNC_NAME] = func->second;
    return func->second;
}

bool LgsIterable::unpackLoopVars(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() != 1) return false;
    const auto iterIndex = new LgsIterIndex(loop->iterExpr, LGS_SIZE.getZeroValue());
    iterIndex->setType(baseType);
    loop->loopVars[0]->expr = iterIndex;
    loop->loopVars[0]->type = iterIndex->type;
    return true;
}

void LgsIterable::unpackIR(LgsLLVMGen& cg, const std::vector<LgsVarDec*> varDecs, Value* iterPtr, Value* index) const {
    const auto iterIndex = varDecs[0]->expr->asIterIndex();
    iterIndex->index.from->IRValue = index;
    iterIndex->setIRElementPtr(cg);
    varDecs[0]->IRValue = iterIndex->IRValue;
}

LgsFunc* LgsIterable::getLenFunc() {
    const auto func = methods.find(LEN_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(LEN_FUNC_NAME, &LGS_SIZE, {this}, BUILTIN | PUBLIC | METHOD);
    methods[LEN_FUNC_NAME] = func->second;
    return func->second;
}

LgsFunc* LgsIterable::getIsEmptyFunc() {
    const auto func = methods.find(IS_EMPTY_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(IS_EMPTY_FUNC_NAME, &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);
    methods[IS_EMPTY_FUNC_NAME] = func->second;
    return func->second;
}

LgsFunc* LgsIterable::getIsNotEmptyFunc() {
    const auto func = methods.find(IS_NOT_EMPTY_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(IS_NOT_EMPTY_FUNC_NAME, &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);;;
    methods[IS_NOT_EMPTY_FUNC_NAME] = func->second;
    return func->second;
}

Value* LgsIterable::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    assert(0);
}

LgsIterable::~LgsIterable() {
    if (sizeExpr) {
        freeExpr(sizeExpr);
        sizeExpr = nullptr;
    }
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
