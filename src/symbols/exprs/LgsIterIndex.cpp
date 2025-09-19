#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVariable.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsVoid.h"
#include <exprs/LgsArrayExpr.h>
#include "types/iterables/LgsMap.h"

Value* LgsIterIndex::loadIR(LgsLLVMGen& cg) {
    const auto baseExprType = baseExpr->type;
    if (const auto map = baseExprType->asMap()) {
        return loadFromMap(cg, map);
    }
    if (const auto arr = baseExprType->asDArray()) {
        return loadFromDArray(cg, arr);
    }
    if (baseExprType->asSArray()) {
        return loadFromSArray(cg);
    }
    if (baseExprType->asVec()) {
        return loadFromVec(cg);
    }
    if (baseExprType->asStr()) {
        return loadFromStr(cg);
    }
    assert(0);
}

Value* LgsIterIndex::loadFromDArray(LgsLLVMGen& cg, const LgsDArray* arr) const {
    auto indexIRValue = index->from->IRValue;
    indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
    const auto rv = arr->getFunc->callIR(cg, {IRValue, indexIRValue});
    const auto valueTy = arr->baseType->getIRType(cg);
    return cg.builder.CreateLoad(valueTy, rv);;
}

Value* LgsIterIndex::loadFromMap(LgsLLVMGen& cg, const LgsMap* map) const {
    const auto mapPtr = IRValue;
    const auto key = index->from->IRValue;
    const auto rv = map->getFunc->callIR(cg, {mapPtr, key});
    const auto valueTy = map->typePair->value->getIRType(cg);
    return cg.builder.CreateLoad(valueTy, rv);
}

Value* LgsIterIndex::loadFromStr(LgsLLVMGen& cg) const {
    if (index->to) {
        const auto intFrom = index->from->asIntConst();
        const auto intTo = index->to->asIntConst();
        const auto strConst = baseExpr->getConstStr();
        return cg.getIRStr(strConst.substr(intFrom->value, intTo->value));
    }
    auto& builder = cg.builder;
    const auto baseExprIRType = baseExpr->type->getIRType(cg);
    const auto ptr = builder.CreateAlloca(baseExprIRType);
    const auto vaArgInst = builder.CreateVAArg(IRValue, baseExprIRType);
    builder.CreateStore(vaArgInst, ptr);
    return builder.CreateLoad(baseExprIRType, ptr);
}

Value* LgsIterIndex::loadFromVec(LgsLLVMGen& cg) const {
    const auto ptr = IRValue;
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
            ptr = iterIndex->IRValue;
            ty = iterIndex->baseExpr->type->getIRType(cg);
            IRIndices.push_back(cg.i32Zero());
            break;
        }
    }
    reverse(IRIndices.begin(), IRIndices.end());
    return cg.builder.CreateGEP(ty, ptr, IRIndices);
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
        LgsFunc putFunc("put", &LGS_VOID, {arr, &LGS_INT, &LGS_ANY}, BUILTIN | METHOD);
        putFunc.callIR(cg, {baseIRValue->IRValue, index->from->IRValue, ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        cg.builder.CreateStore(rIRValue, loadFromSArray(cg));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        map->getAddFunc()->call(cg, {baseExpr, index->from, expr});
    } else {
        cg.builder.CreateStore(rIRValue, IRValue);
    }
}

void LgsIterIndex::assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const {
    assert(0);
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
