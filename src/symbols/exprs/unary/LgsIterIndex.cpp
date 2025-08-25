#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"

Value* LgsIterIndex::loadIR(LgsLLVM& codeGen) {
    const auto baseExprType = baseExpr->type;
    if (baseExprType->asSArray()) {
        IRValue = loadFromSArray(codeGen);
    } else if (baseExpr->type->isVector()) {
        IRValue = loadFromVec(codeGen);
    } else if (const auto arr = baseExprType->asDArray()) {
        IRValue = loadFromDArray(codeGen, arr);
    } else if (const auto map = baseExprType->asMap()) {
        IRValue = loadFromMap(codeGen, map);
    } else if (const auto str = baseExprType->asStr()) {
        IRValue = loadFromStr(codeGen, str);
    } else {
        assert(0);
    }
    return IRValue;
}

Value* LgsIterIndex::loadFromDArray(LgsLLVM& codeGen, const LgsDArray* arr) const {
    const auto arrPtr = baseExpr->IRValue;
    auto indexIRValue = index->from->IRValue;
    indexIRValue = codeGen.builder.CreateZExt(indexIRValue, codeGen.i64Ty());
    const auto rv = arr->getFunc->callIR(codeGen, {arrPtr, indexIRValue});
    const auto valueTy = arr->baseType->getIRType(codeGen);
    return codeGen.builder.CreateLoad(valueTy, rv);;
}

Value* LgsIterIndex::loadFromMap(LgsLLVM& codeGen, const LgsMap* map) const {
    const auto mapPtr = baseExpr->IRValue;
    const auto key = index->from->IRValue;
    const auto rv = map->getFunc->callIR(codeGen, {mapPtr, key});
    const auto valueTy = map->typePair->value->getIRType(codeGen);
    return codeGen.builder.CreateLoad(valueTy, rv);
}

Value* LgsIterIndex::loadFromStr(LgsLLVM& codeGen, const LgsStr* str) const {
    if (index->to) return createStrSlice(codeGen, str);
    auto& builder = codeGen.builder;
    const auto baseExprIRValue = baseExpr->IRValue;
    const auto baseExprIRType = baseExpr->type->getIRType(codeGen);
    const auto ptr = builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    builder.CreateStore(vaArgInst, ptr);
    return builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::loadFromVec(LgsLLVM& codeGen) const {
    const auto ptr = baseExpr->IRValue;
    const auto vec = codeGen.builder.CreateLoad(baseExpr->type->getIRType(codeGen), ptr);
    const auto i = index->from->IRValue;
    return codeGen.builder.CreateExtractElement(vec, i);
}

Value* LgsIterIndex::loadFromSArray(LgsLLVM& codeGen) const {
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

Value* LgsIterIndex::createStrSlice(LgsLLVM& codeGen, const LgsStr* str) const {
    const auto intFrom = index->from->asIntConst();
    const auto intTo = index->to->asIntConst();
    const auto strConst = baseExpr->getConstStr();
    return codeGen.getIRStr(strConst.substr(intFrom->value, intTo->value));
}

Value* LgsIterIndex::getStrGEP(LgsLLVM& codeGen) const {
    const auto ty = baseExpr->type->getIRType(codeGen);
    const auto value = baseExpr->IRValue;
    const auto iValue = index->from->IRValue;
    return codeGen.builder.CreateGEP(ty, value, {codeGen.i32Zero(), iValue});
}

void LgsIterIndex::assign(LgsLLVM& codeGen, LgsExpr* expr) {
    if (const auto map = expr->asHashMap()) {
        assignHashMap(codeGen, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        assignArray(codeGen, arr);
    } else {
        assignScalar(codeGen, expr);
    }
}

void LgsIterIndex::assignScalar(LgsLLVM& codeGen, LgsExpr* expr) {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    if (const auto arr = baseExpr->type->asDArray()) {
        const auto ptr = codeGen.builder.CreateAlloca(expr->type->getIRType(codeGen));
        codeGen.builder.CreateStore(rIRValue, ptr);
        arr->putFunc->callIR(codeGen, {baseIRValue->IRValue, index->from->IRValue, ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        codeGen.builder.CreateStore(rIRValue, loadFromSArray(codeGen));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        map->addFunc->call(codeGen, {baseExpr, index->from, expr});
    } else {
        codeGen.builder.CreateStore(rIRValue, IRValue);
    }
}

void LgsIterIndex::assignArray(LgsLLVM& codeGen, const LgsArrayExpr* arr) const {
    // const auto IRType = baseExpr->type->getIRType(codeGen);
    // const auto arrPtr = baseExpr->IRValue;
    //
    // // Flatten the indices and reverse them.
    // std::vector<LgsIndex*> indices;
    // auto iterIndex = this;
    // while (iterIndex) {
    //     if (iterIndex->index) indices.push_back(iterIndex->index);
    //     iterIndex = baseExpr->asIterIndex();
    // }
    // reverse(indices.begin(), indices.end());
    //
    // std::vector<Value*> IRIndices = {codeGen.i32Zero()};
    // for (const auto i : indices) {
    //     IRIndices.emplace_back(i->from->IRValue);
    // }
    // for (int i = 0; i < arr->initialElements.size(); ++i) {
    //     const auto element = arr->initialElements[i];
    //     const auto IRIndex = codeGen.i32(i);
    //     IRIndices.push_back(IRIndex);
    //     const auto gep = codeGen.builder.CreateGEP(IRType, arrPtr, IRIndices);
    //     const auto rValue = element->IRValue;
    //     codeGen.builder.CreateStore(rValue, gep);
    //     IRIndices.pop_back();
    // }
}

void LgsIterIndex::assignHashMap(LgsLLVM& codeGen, LgsHashMap* map) {
    assert(0);
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
