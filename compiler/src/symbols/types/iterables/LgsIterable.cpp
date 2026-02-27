#include "types/iterables/LgsIterable.h"

#include <assert.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <unordered_map>
#include <utility>
#include <vector>

#include "exprs/LgsIterIndex.h"
#include "loops/LgsForeachLoop.h"
#include "stmts/LgsVarDec.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/iterables/LgsDArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsVoid.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsFuncType.h"
#include "types/LgsTypeParam.h"

namespace llvm {
class Value;
}

LgsFunc* LgsIterable::getMethod(const std::string& methodName) {
    if (methods.contains(methodName)) return methods[methodName];
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == LEN_FUNC) {
        const auto func = new LgsFunc(methodName, getBaseName(), &LGS_SIZE, {this}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsVarDec>& args) {
            return lenIR(cg, args.front().expr->IRValue);
        };
        addMethod(func);
        return func;
    }
    if (methodName == IS_EMPTY_FUNC) {
        const auto func = new LgsFunc(methodName, getBaseName(), &LGS_BOOL, {this}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsVarDec>& args) {
            return cg.builder.CreateICmpEQ(lenIR(cg, args.front().expr->IRValue), cg.zeroSize());
        };
        addMethod(func);
        return func;
    }
    if (methodName == NOT_EMPTY_FUNC) {
        const auto func = new LgsFunc(methodName, getBaseName(), &LGS_BOOL, {this}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsVarDec>& args) {
            return cg.builder.CreateICmpSGT(lenIR(cg, args.front().expr->IRValue), cg.zeroSize());
        };
        addMethod(func);
        return func;
    }
    if (methodName == MAP_FUNC) {
        // map<T, U>(arr: T[], cb: (T): U): U[]
        const auto T = new LgsTypeParam("T");
        const auto U = new LgsTypeParam("U");
        const auto callback = new LgsFuncType("cb", U, {LgsParam(T)});
        const auto func = new LgsFunc(methodName, getBaseName(), new LgsDArray(U), {new LgsDArray(T), callback}, flags);
        func->funcType->typeParams.push_back(T);
        func->funcType->typeParams.push_back(U);
        callback->typeParams.push_back(T);
        callback->typeParams.push_back(U);
        addMethod(func);
        return func;
    }
    if (methodName == FILTER_FUNC) {
        const auto T = new LgsTypeParam("T");
        const auto callback = new LgsFuncType("cb", &LGS_BOOL, {LgsParam(baseType)});
        const auto func = new LgsFunc(methodName, getBaseName(), new LgsDArray(baseType), {this, callback}, flags);
        func->funcType->typeParams.push_back(T);
        callback->typeParams.push_back(T);
        addMethod(func);
        return func;
    }
    if (methodName == FOREACH_FUNC) {
        const auto generic = new LgsTypeParam("T");
        const auto callback = new LgsFuncType("cb", &LGS_VOID, {LgsParam(baseType)});
        const auto func = new LgsFunc(methodName, &LGS_VOID, {this, callback}, flags);
        func->funcType->typeParams.push_back(generic);
        callback->typeParams.push_back(generic);
        addMethod(func);
        return func;
    }
    return LgsType::getMethod(methodName);
}

LgsType* LgsIterable::getNestedBaseType() const {
    auto nestedIter = this;
    while (true) {
        if (nestedIter->baseType->asStr()) return nestedIter->baseType;
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            nestedIter = innerIter;
        } else {
            return nestedIter->baseType;
        }
    }
}

void LgsIterable::setNestedBaseType(LgsType* newBaseType) {
    auto nestedIter = this;
    while (true) {
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            if (innerIter->asStr()) {
                nestedIter->baseType = newBaseType;
                return;
            }
            nestedIter = innerIter;
        } else {
            nestedIter->baseType = newBaseType;
            return;
        }
    }
}

size_t LgsIterable::getDims() const {
    size_t dims = 0;
    auto nestedIter = this;
    while (true) {
        dims++;
        if (const auto innerIter = nestedIter->baseType->asIterable()) {
            nestedIter = innerIter;
        } else {
            break;
        }
    }
    return dims;
}

bool LgsIterable::hasTypeParams() {
    return baseType && baseType->hasTypeParams();
}

bool LgsIterable::isRecursive(std::unordered_set<std::string>& visited) const {
    return baseType && baseType->isRecursive(visited);
}

std::optional<size_t> LgsIterable::getConstLength() {
    return std::nullopt;
}

LgsType* LgsIterable::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsIterable::getValueType() {
    return baseType;
}

bool LgsIterable::unpackLoopVars(LgsForeachLoop* loop) const {
    if (loop->loopVars.size() > 2) return false;
    assert(baseType);
    const auto iterIndex = new LgsIterIndex(loop->iterExpr, LGS_SIZE.getZeroValue());
    iterIndex->setType(baseType);
    if (loop->loopVars.size() == 1) {
        loop->loopVars[0]->expr = iterIndex;
        loop->loopVars[0]->setType(iterIndex->type);
    } else if (loop->loopVars.size() == 2) {
        loop->loopVars[0]->expr = LGS_SIZE.getZeroValue();
        loop->loopVars[0]->setType(&LGS_SIZE);
        loop->loopVars[1]->expr = iterIndex;
        loop->loopVars[1]->setType(iterIndex->type);
    }
    return true;
}

void LgsIterable::setLoopIRVars(LgsCodeGen& cg, LgsForeachLoop* loop) {
    const auto varsCount = loop->loopVars.size();
    const auto iterIndex = loop->loopVars[varsCount == 1 ? 0 : 1]->expr->asIterIndex();
    const auto iterable = iterIndex->baseExpr->type->asIterable();
    iterIndex->index.from->IRValue = loop->loadIndex(cg);
    iterIndex->IRValue = iterable->getIRElement(cg, iterIndex->baseExpr->IRValue, iterIndex->index.from->IRValue);
    if (varsCount == 1) {
        loop->loopVars[0]->IRValue = iterIndex->IRValue;
    } else if (varsCount == 2) {
        loop->loopVars[0]->IRValue = loop->loadIndex(cg);
        loop->loopVars[1]->IRValue = iterIndex->IRValue;
    }
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
