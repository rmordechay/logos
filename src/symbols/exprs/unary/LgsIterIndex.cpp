#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsVarDec.h"
#include <exprs/unary/LgsArrayExpr.h>
#include "types/LgsMap.h"

Value* LgsIterIndex::loadIR(LgsLLVMGen& cg) {
    const auto baseExprType = baseExpr->type;
    if (baseExprType->asSArray()) {
        IRValue = loadFromSArray(cg);
    } else if (baseExpr->type->asVec()) {
        IRValue = loadFromVec(cg);
    } else if (const auto arr = baseExprType->asDArray()) {
        IRValue = loadFromDArray(cg, arr);
    } else if (const auto map = baseExprType->asMap()) {
        IRValue = loadFromMap(cg, map);
    } else if (const auto str = baseExprType->asStr()) {
        IRValue = loadFromStr(cg, str);
    } else {
        assert(0);
    }
    return IRValue;
}

Value* LgsIterIndex::loadFromDArray(LgsLLVMGen& cg, const LgsDArray* arr) const {
    const auto arrPtr = baseExpr->IRValue;
    auto indexIRValue = index->from->IRValue;
    indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
    const auto rv = arr->getFunc->callIR(cg, {arrPtr, indexIRValue});
    const auto valueTy = arr->baseType->getIRType(cg);
    return cg.builder.CreateLoad(valueTy, rv);;
}

Value* LgsIterIndex::loadFromMap(LgsLLVMGen& cg, const LgsMap* map) const {
    const auto mapPtr = baseExpr->IRValue;
    const auto key = index->from->IRValue;
    const auto rv = map->getFunc->callIR(cg, {mapPtr, key});
    const auto valueTy = map->typePair->value->getIRType(cg);
    return cg.builder.CreateLoad(valueTy, rv);
}

Value* LgsIterIndex::loadFromStr(LgsLLVMGen& cg, const LgsStr* str) const {
    if (index->to) return createStrSlice(cg, str);
    auto& builder = cg.builder;
    const auto baseExprIRValue = baseExpr->IRValue;
    const auto baseExprIRType = baseExpr->type->getIRType(cg);
    const auto ptr = builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = builder.CreateVAArg(baseExprIRValue, baseExprIRType);
    builder.CreateStore(vaArgInst, ptr);
    return builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::loadFromVec(LgsLLVMGen& cg) const {
    const auto ptr = baseExpr->IRValue;
    const auto vec = cg.builder.CreateLoad(baseExpr->type->getIRType(cg), ptr);
    const auto i = index->from->IRValue;
    return cg.builder.CreateExtractElement(vec, i);
}

Value* LgsIterIndex::loadFromSArray(LgsLLVMGen& cg) const {
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
            ty = iterIndex->baseExpr->type->getIRType(cg);
            IRIndices.push_back(cg.i32Zero());
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return cg.builder.CreateGEP(ty, ptr, IRIndices);
}

Value* LgsIterIndex::createStrSlice(LgsLLVMGen& cg, const LgsStr* str) const {
    const auto intFrom = index->from->asIntConst();
    const auto intTo = index->to->asIntConst();
    const auto strConst = baseExpr->getConstStr();
    return cg.getIRStr(strConst.substr(intFrom->value, intTo->value));
}

Value* LgsIterIndex::getStrGEP(LgsLLVMGen& cg) const {
    const auto ty = baseExpr->type->getIRType(cg);
    const auto value = baseExpr->IRValue;
    const auto iValue = index->from->IRValue;
    return cg.builder.CreateGEP(ty, value, {cg.i32Zero(), iValue});
}

void LgsIterIndex::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    if (const auto map = expr->asHashMap()) {
        assignHashMap(cg, map);
    } else if (const auto arr = expr->asArrayExpr()) {
        assignArray(cg, arr);
    } else {
        assignScalar(cg, expr);
    }
}

void LgsIterIndex::assignScalar(LgsLLVMGen& cg, LgsExpr* expr) {
    const auto rIRValue = expr->IRValue;
    const auto baseIRValue = baseExpr;
    if (const auto arr = baseExpr->type->asDArray()) {
        const auto ptr = cg.builder.CreateAlloca(expr->type->getIRType(cg));
        cg.builder.CreateStore(rIRValue, ptr);
        arr->putFunc->callIR(cg, {baseIRValue->IRValue, index->from->IRValue, ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        cg.builder.CreateStore(rIRValue, loadFromSArray(cg));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        map->addFunc->call(cg, {baseExpr, index->from, expr});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
}

void LgsIterIndex::assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const {
    // const auto IRType = baseExpr->type->getIRType(cg);
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
    // std::vector<Value*> IRIndices = {cg.i32Zero()};
    // for (const auto i : indices) {
    //     IRIndices.emplace_back(i->from->IRValue);
    // }
    // for (int i = 0; i < arr->initialElements.size(); ++i) {
    //     const auto element = arr->initialElements[i];
    //     const auto IRIndex = cg.i32(i);
    //     IRIndices.push_back(IRIndex);
    //     const auto gep = cg.builder.CreateGEP(IRType, arrPtr, IRIndices);
    //     const auto rValue = element->IRValue;
    //     cg.builder.CreateStore(rValue, gep);
    //     IRIndices.pop_back();
    // }
}

void LgsIterIndex::assignHashMap(LgsLLVMGen& cg, LgsHashMap* map) {
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
