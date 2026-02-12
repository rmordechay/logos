#include "types/iterables/LgsIterable.h"
#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include "LgsUtils.h"
#include "exprs/constants/LgsIntConst.h"
#include "funcs/LgsFunc.h"
#include "types/iterables/LgsMap.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsVoid.h"

LgsFunc* LgsIterable::getMethod(const std::string& methodName) {
    if (methods.contains(methodName)) return methods[methodName];
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == LEN_FUNC) {
        const auto func = new LgsFunc(methodName, getBaseName(), &LGS_SIZE, {this}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            return lenIR(cg, args.front().expr->IRValue);
        };
        addMethod(func);
        return func;
    }
    if (methodName == IS_EMPTY_FUNC) {
        const auto func = new LgsFunc(methodName, getBaseName(), &LGS_BOOL, {this}, flags);
        addMethod(func);
        return func;
    }
    if (methodName == NOT_EMPTY_FUNC) {
        const auto func = new LgsFunc(methodName, getBaseName(), &LGS_BOOL, {this}, flags);
        addMethod(func);
        return func;
    }
    if (methodName == MAP_FUNC) {
        // map<T, U>(arr: T[], cb: (e: T): U): U[]
        const auto U = new LgsGenericType("T");
        const auto T = new LgsGenericType("U");
        const auto callback = new LgsFuncType("cb", U, {LgsParam(T)});
        const auto func = new LgsFunc(methodName, getBaseName(), new LgsDArray(U), {this, callback}, flags);
        func->funcType->genericTypes.push_back(T);
        func->funcType->genericTypes.push_back(U);
        callback->genericTypes.push_back(T);
        callback->genericTypes.push_back(U);
        addMethod(func);
        return func;
    }
    if (methodName == FILTER_FUNC) {
        const auto generic = new LgsGenericType("T"); // T is baseType
        const auto callback = new LgsFuncType("cb", &LGS_BOOL, {LgsParam(baseType)});
        const auto func = new LgsFunc(methodName, getBaseName(), new LgsDArray(baseType), {this, callback}, flags);
        func->funcType->genericTypes.push_back(generic);
        callback->genericTypes.push_back(generic);
        addMethod(func);
        return func;
    }
    if (methodName == FOREACH_FUNC) {
        const auto generic = new LgsGenericType("T"); // T is baseType
        const auto callback = new LgsFuncType("cb", &LGS_VOID, {LgsParam(baseType)});
        const auto func = new LgsFunc(methodName, &LGS_VOID, {this, callback}, flags);
        func->funcType->genericTypes.push_back(generic);
        callback->genericTypes.push_back(generic);
        addMethod(func);
        return func;
    }
    return LgsType::getMethod(methodName);
}

LgsType* LgsIterable::getNestedBaseType() const {
    auto nestedIter = this;
    while (true) {
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            nestedIter = innerIter;
        } else {
            return nestedIter->baseType;
        }
    }
}

void LgsIterable::setBaseType(LgsType* newBaseType) {
    auto nestedIter = this;
    while (true) {
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            nestedIter = innerIter;
        } else {
            nestedIter->baseType = newBaseType;
            break;
        }
    }
}

std::optional<int64_t> LgsIterable::getConstLength() {
    return std::nullopt;
}

LgsType* LgsIterable::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsIterable::getValueType() {
    return baseType;
}

bool LgsIterable::unpackLoopVars(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() > 1) return false;
    assert(baseType);
    const auto iterIndex = new LgsIterIndex(loop->iterExpr, new LgsIntConst(&LGS_SIZE, 0));
    iterIndex->setType(baseType);
    loop->loopVars[0]->expr = iterIndex;
    loop->loopVars[0]->setType(iterIndex->type);
    return true;
}

void LgsIterable::setLoopIRVars(LgsCodeGen& cg, LgsForeachLoop* loop) {
    const auto iterIndex = loop->loopVars[0]->expr->asIterIndex();
    const auto iterable = iterIndex->baseExpr->type->asIterable();
    iterIndex->index.from->IRValue = loop->loadIndex(cg);
    iterIndex->IRValue = iterable->getIRElement(cg, iterIndex->baseExpr->IRValue, iterIndex->index.from->IRValue);
    loop->loopVars[0]->IRValue = iterIndex->IRValue;
}

void LgsIterable::addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) {
    assert(0);
}

LgsIterable::~LgsIterable() {
    for (auto [name, method] : methods) {
        if (name == MAP_FUNC || name == FILTER_FUNC || name == FOREACH_FUNC) {
            method->funcType->rt = nullptr;
            method->funcType->params[0].type = nullptr;
            const auto& ft = method->funcType->params[1].type->asFuncType();
            ft->rt = nullptr;
            ft->params[0].type = nullptr;
        }
    }
    baseType = nullptr;
}
