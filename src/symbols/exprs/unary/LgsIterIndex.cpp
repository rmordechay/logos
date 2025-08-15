#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"

void LgsIterIndex::createIRValue(LgsCodeGen* codeGen) {
    const auto baseExprType = baseExpr->type;
    if (baseExprType->asSArray()) {
        IRValue = getArrGEP(codeGen);
    } else if (const auto arr = baseExprType->asDArray()) {
        IRValue = createIRFromArray(codeGen, arr);
    } else if (const auto map = baseExprType->asMap()) {
        IRValue = createIRFromMap(codeGen, map);
    } else if (const auto str = baseExprType->asStr()) {
        IRValue = createIRFromStr(codeGen, str);
    }
    assert(0);
}

Value* LgsIterIndex::createIRFromStr(LgsCodeGen* codeGen, const LgsStr* str) const {
    if (index->to) return createStrSlice(codeGen, str);
    const auto baseExprIRValue = baseExpr->getIRValue(codeGen);
    const auto baseExprIRType = baseExpr->type->getIRType(codeGen);
    const auto ptr = codeGen->builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = codeGen->builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    codeGen->builder.CreateStore(vaArgInst, ptr);
    return codeGen->builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::createIRFromArray(LgsCodeGen* codeGen, LgsDArray* arr) const {
    auto& builder = codeGen->builder;
    const auto arrPtr = baseExpr->getIRValue(codeGen);
    auto indexIRValue = index->from->getIRValue(codeGen);
    indexIRValue = builder.CreateZExt(indexIRValue, codeGen->i64Ty());
    return arr->getFunc.callIR(codeGen, {arrPtr, indexIRValue});
}

Value* LgsIterIndex::createIRFromMap(LgsCodeGen* codeGen, LgsMap* map) const {
    const auto mapPtr = baseExpr->getIRValue(codeGen);
    const auto key = index->from->getIRValue(codeGen);
    return map->getFunc.callIR(codeGen, {mapPtr, key});
}

Value* LgsIterIndex::createStrSlice(LgsCodeGen* codeGen, const LgsStr* str) const {
    const auto intFrom = index->from->asIntConst();
    const auto intTo = index->to->asIntConst();
    const auto strConst = baseExpr->getConstStr();
    return codeGen->getIRStr(strConst.substr(intFrom->value, intTo->value));
}

Value* LgsIterIndex::getStrGEP(LgsCodeGen* codeGen) const {
    const auto ty = baseExpr->type->getIRType(codeGen);
    const auto value = baseExpr->getIRValue(codeGen);
    const auto iValue = index->from->getIRValue(codeGen);
    return codeGen->builder.CreateGEP(ty, value, {codeGen->i32Zero(), iValue});
}

Value* LgsIterIndex::getArrGEP(LgsCodeGen* codeGen) const {
    std::vector<Value*> IRIndices = {};
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index->from->getIRValue(codeGen);
        IRIndices.push_back(irValue);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->baseExpr->getIRValue(codeGen);
            ty = iterIndex->baseExpr->type->getIRType(codeGen);
            IRIndices.push_back(codeGen->i32Zero());
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return codeGen->builder.CreateGEP(ty, ptr, IRIndices);
}

std::string LgsIterIndex::prettyName() {
    std::stringstream str;
    str << baseExpr->prettyName();
    if (index->to) {
        str << '[' << index->from->prettyName() << ':' << index->to->prettyName() << ']';
    } else {
        str << '[' << index->from->prettyName() << ']';
    }
    return str.str();
}

LgsIterIndex::~LgsIterIndex() {
    delete baseExpr;
    delete index->from;
    delete index->to;
    delete index;
}
