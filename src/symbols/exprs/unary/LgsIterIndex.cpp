#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"

Value* LgsIterIndex::loadFromDArray(LgsCodeGen& codeGen, const LgsDArray* arr) const {
    const auto arrPtr = baseExpr->IRValue;
    auto indexIRValue = index->from->IRValue;
    indexIRValue = codeGen.builder.CreateZExt(indexIRValue, codeGen.i64Ty());
    return arr->getFunc->callIR(codeGen, {arrPtr, indexIRValue});
}

Value* LgsIterIndex::loadFromMap(LgsCodeGen& codeGen, const LgsMap* map) const {
    const auto mapPtr = baseExpr->IRValue;
    const auto key = index->from->IRValue;
    return map->getFunc->callIR(codeGen, {mapPtr, key});
}

Value* LgsIterIndex::loadFromStr(LgsCodeGen& codeGen, const LgsStr* str) const {
    if (index->to) return createStrSlice(codeGen, str);
    auto& builder = codeGen.builder;
    const auto baseExprIRValue = baseExpr->IRValue;
    const auto baseExprIRType = baseExpr->type->getIRType(codeGen);
    const auto ptr = builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    builder.CreateStore(vaArgInst, ptr);
    return builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::loadFromVec(LgsCodeGen& codeGen) const {
    const auto ptr = baseExpr->IRValue;
    const auto vec = codeGen.builder.CreateLoad(baseExpr->type->getIRType(codeGen), ptr);
    const auto i = index->from->IRValue;
    return codeGen.builder.CreateExtractElement(vec, i);
}

Value* LgsIterIndex::createStrSlice(LgsCodeGen& codeGen, const LgsStr* str) const {
    const auto intFrom = index->from->asIntConst();
    const auto intTo = index->to->asIntConst();
    const auto strConst = baseExpr->getConstStr();
    return codeGen.getIRStr(strConst.substr(intFrom->value, intTo->value));
}

Value* LgsIterIndex::loadFromSArray(LgsCodeGen& codeGen) const {
    std::vector<Value*> IRIndices = {};
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index->from->IRValue;
        IRIndices.push_back(irValue);
        const auto innerIterIndex = iterIndex->baseExpr->asIterIndex();
        if (innerIterIndex) {
            iterIndex = innerIterIndex;
        } else {
            ptr = iterIndex->baseExpr->IRValue;
            ty = iterIndex->baseExpr->type->getIRType(codeGen);
            IRIndices.push_back(codeGen.i32Zero());
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return codeGen.builder.CreateGEP(ty, ptr, IRIndices);
}

Value* LgsIterIndex::getStrGEP(LgsCodeGen& codeGen) const {
    const auto ty = baseExpr->type->getIRType(codeGen);
    const auto value = baseExpr->IRValue;
    const auto iValue = index->from->IRValue;
    return codeGen.builder.CreateGEP(ty, value, {codeGen.i32Zero(), iValue});
}

std::string LgsIterIndex::pname() {
    std::stringstream str;
    str << baseExpr->pname();
    if (index->to) {
        str << '[' << index->from->pname() << ':' << index->to->pname() << ']';
    } else {
        str << '[' << index->from->pname() << ']';
    }
    return str.str();
}

json::value LgsIterIndex::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "iterIndex";
    jsonObj["from"] = index->from->asJSON();
    if (index->to) jsonObj["to"] = index->to->asJSON();
    jsonObj["baseExpr"] = baseExpr->asJSON();
    return jsonObj;
}

LgsIterIndex::~LgsIterIndex() {
    if (baseExpr) {
        delete baseExpr;
        baseExpr = nullptr;
    }
    if (index) {
        delete index;
        index = nullptr;
    }
}
