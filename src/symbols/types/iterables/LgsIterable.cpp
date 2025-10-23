#include "types/iterables/LgsIterable.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/constants/LgsIntConst.h"
#include "funcs/LgsFunc.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

LgsFunc* LgsIterable::getMethod(const std::string& methodName) {
    const auto method = methods.find(methodName);
    if (method != methods.end()) {
        if (method->second) {
            return method->second;
        }
        const auto iter = asIterable();
        if (methodName == ADD_FUNC_NAME) {
            return iter->getAddFunc();
        }
        if (methodName == LEN_FUNC_NAME) {
            return iter->getLenFunc();
        }
        if (methodName == IS_EMPTY_FUNC_NAME) {
            return iter->getIsEmptyFunc();
        }
        if (methodName == IS_NOT_EMPTY_FUNC_NAME) {
            return iter->getIsNotEmptyFunc();
        }
        if (methodName == MAP_FUNC_NAME) {
            return iter->getMapFunc();
        }
        if (methodName == FILTER_FUNC_NAME) {
            return iter->getFilterFunc();
        }
        assert(0);
    }
    return nullptr;
}

size_t LgsIterable::getDimension() const {
    size_t dim = 1;
    auto nestedIter = this;
    while (true) {
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            nestedIter = innerIter;
            if (innerIter->asVec() || innerIter->asStr()) continue;
            dim++;
        } else {
            break;
        }
    }
    return dim;
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

LgsFunc* LgsIterable::getAddFunc() {
    return nullptr;
}

LgsFunc* LgsIterable::getMapFunc() {
    const auto func = methods.find(MAP_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(MAP_FUNC_NAME, this, {this, new LgsFuncType(baseType, {LgsParam(baseType, "")})}, BUILTIN | PUBLIC | METHOD);
    methods[MAP_FUNC_NAME] = func->second;
    return func->second;
}

LgsFunc* LgsIterable::getFilterFunc() {
    const auto func = methods.find(FILTER_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(FILTER_FUNC_NAME, this, {this, new LgsFuncType(&LGS_BOOL, {LgsParam(baseType, "")})}, BUILTIN | PUBLIC | METHOD);
    methods[FILTER_FUNC_NAME] = func->second;
    return func->second;
}

LgsType* LgsIterable::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsIterable::getValueType() {
    return baseType;
}

bool LgsIterable::unpackLoopVarsTypes(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() != 1) return false;
    const auto iterIndex = new LgsIterIndex(loop->iterExpr, LGS_SIZE.getZeroValue());
    iterIndex->setType(baseType);
    loop->loopVars[0]->expr = iterIndex;
    loop->loopVars[0]->type = iterIndex->type;
    return true;
}

void LgsIterable::unpackLoopIR(LgsLLVMGen& cg, LgsForeachLoop* loop) const {
    const auto iterIndex = loop->loopVars[0]->expr->asIterIndex();
    iterIndex->index.from->IRValue = loop->iValue;
    iterIndex->setIRElementPtr(cg);
    loop->loopVars[0]->IRValue = iterIndex->IRValue;
}

Value* LgsIterable::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    assert(0);
}

LgsIterable::~LgsIterable() {
    if (size) {
        freeExpr(size);
        size = nullptr;
    }
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
