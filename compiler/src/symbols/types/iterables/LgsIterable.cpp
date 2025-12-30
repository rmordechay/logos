#include "types/iterables/LgsIterable.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include "LgsUtils.h"
#include "funcs/LgsFunc.h"
#include "types/iterables/LgsMap.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsVoid.h"

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

LgsFunc* LgsIterable::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == LEN_FUNC) {
        if (methods.contains(LEN_FUNC)) return methods[LEN_FUNC];
        const auto func = new LgsFunc(LEN_FUNC, getBaseName(), &LGS_SIZE, {this}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            return lenIR(cg, args.front().expr->IRValue);
        };
        addMethod(func);
        return func;
    }
    if (methodName == IS_EMPTY_FUNC) {
        if (methods.contains(IS_EMPTY_FUNC)) return methods[IS_EMPTY_FUNC];
        const auto func = new LgsFunc(IS_EMPTY_FUNC, getBaseName(), &LGS_BOOL, {this}, flags);
        addMethod(func);
        return func;
    }
    if (methodName == NOT_EMPTY_FUNC) {
        if (methods.contains(NOT_EMPTY_FUNC)) return methods[NOT_EMPTY_FUNC];
        const auto func = new LgsFunc(NOT_EMPTY_FUNC, getBaseName(), &LGS_BOOL, {this}, flags);
        addMethod(func);
        return func;
    }
    if (methodName == MAP_FUNC) {
        if (methods.contains(MAP_FUNC)) return methods[MAP_FUNC];
        const auto generic = new LgsGenericType("T");
        const auto callback = new LgsFuncType(generic, {LgsParam(baseType)});
        const auto func = new LgsFunc(MAP_FUNC, getBaseName(), new LgsDArray(generic), {this, callback}, flags);
        func->funcType->genericTypes.push_back(generic);
        callback->genericTypes.push_back(generic);
        addMethod(func);
        return func;
    }
    if (methodName == FILTER_FUNC) {
        if (methods.contains(FILTER_FUNC)) return methods[FILTER_FUNC];
        const auto callback = new LgsFuncType(&LGS_BOOL, {LgsParam(baseType)});
        const auto func = new LgsFunc(FILTER_FUNC, getBaseName(), this, {this, callback}, flags);
        addMethod(func);
        return func;
    }
    if (methodName == FOREACH_FUNC) {
        if (methods.contains(FOREACH_FUNC)) return methods[FOREACH_FUNC];
        const auto callback = new LgsFuncType(&LGS_VOID, {LgsParam(baseType)});
        const auto func = new LgsFunc(FOREACH_FUNC, &LGS_VOID, {this, callback}, flags);
        addMethod(func);
        return func;
    }
    return LgsType::getMethod(methodName);
}

LgsType* LgsIterable::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsIterable::getValueType() {
    return baseType;
}

bool LgsIterable::unpackLoopVarsTypes(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() > 1) return false;
    assert(baseType);
    const auto iterIndex = new LgsIterIndex(loop->iterExpr, LGS_SIZE.getZeroValue());
    iterIndex->setType(baseType);
    loop->loopVars[0]->expr = iterIndex;
    loop->loopVars[0]->setType(iterIndex->type);
    return true;
}

void LgsIterable::unpackLoopIR(LgsCgModule& cg, LgsForeachLoop* loop) {
    const auto iterIndex = loop->loopVars[0]->expr->asIterIndex();
    iterIndex->index.from->IRValue = loop->loadIndex(cg);
    iterIndex->setIRElementPtr(cg);
    loop->loopVars[0]->IRValue = iterIndex->IRValue;
}

void LgsIterable::addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) {
    assert(0);
}

LgsIterable::~LgsIterable() {
    freeExpr(size);
    for (auto [name, method] : methods) {
        if (name == MAP_FUNC || name == FILTER_FUNC || name == FOREACH_FUNC) {
            method->funcType->rt = nullptr;
            method->funcType->params[0].type = nullptr;
            const auto& ft = method->funcType->params[1].type->asFuncType();
            ft->rt = nullptr;
            ft->params[0].type = nullptr;
        }
    }
    size = nullptr;
    baseType = nullptr;
}
