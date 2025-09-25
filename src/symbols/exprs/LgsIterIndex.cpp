#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVariable.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/LgsVoid.h"
#include <exprs/LgsArrayExpr.h>
#include "types/iterables/LgsMap.h"
#include "types/iterables/LgsVec.h"

Value* LgsIterIndex::loadIR(LgsLLVMGen& cg) {
    const auto baseExprType = baseExpr->type;
    if (baseExprType->asMap()) {
        return loadFromMap(cg);
    }
    if (baseExprType->asDArray()) {
        return loadFromDArray(cg);
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

void LgsIterIndex::setIRElementPtr(LgsLLVMGen& cg) {
    const auto baseExprType = baseExpr->type;
    if (const auto sArr = baseExprType->asSArray()) {
        IRValue = IRValue = cg.builder.CreateGEP(sArr->getIRType(cg), baseExpr->IRValue, {cg.i32Zero(), index.from->IRValue});;
    } else if (const auto dArr = baseExpr->type->asDArray()) {
        auto indexIRValue = index.from->IRValue;
        indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
        IRValue = dArr->getIRElement(cg, baseExpr->IRValue, indexIRValue);
    } else if (const auto vec = baseExprType->asVec()) {
        auto indexIRValue = index.from->IRValue;
        indexIRValue = cg.builder.CreateZExt(indexIRValue, cg.i64Ty());
        IRValue = vec->getIRElement(cg, baseExpr->IRValue, indexIRValue);
    } else if (const auto map = baseExpr->type->asMap()) {
        const auto mapPtr = IRValue;
        const auto key = index.from->IRValue;
        IRValue = map->getIRElement(cg, mapPtr, key);
    } else if (baseExprType->asStr()) {
        if (index.to) {
            const auto intFrom = index.from->asIntConst();
            const auto intTo = index.to->asIntConst();
            const auto strConst = baseExpr->getConstStr();
            IRValue = cg.getIRStr(strConst.substr(intFrom->value, intTo->value));
        } else {
            IRValue = cg.builder.CreateGEP(cg.i8Ty(), baseExpr->IRValue, {cg.i32Zero(), index.from->IRValue});
        }
    }
}

Value* LgsIterIndex::loadFromDArray(LgsLLVMGen& cg) {
    const auto arr = baseExpr->type->asDArray();
    const auto valueTy = arr->baseType->getIRType(cg);
    return cg.builder.CreateLoad(valueTy, IRValue);
}

Value* LgsIterIndex::loadFromMap(LgsLLVMGen& cg) {
    const auto map = baseExpr->type->asMap();
    const auto valueTy = map->typePair->value->getIRType(cg);
    return cg.builder.CreateLoad(valueTy, IRValue);
}

Value* LgsIterIndex::loadFromStr(LgsLLVMGen& cg) {
    if (index.to) assert(0);
    return cg.builder.CreateLoad(cg.i8Ty(), IRValue);
}

Value* LgsIterIndex::loadFromVec(LgsLLVMGen& cg) const {
    const auto vec = cg.builder.CreateLoad(baseExpr->type->getIRType(cg), IRValue);
    const auto i = index.from->IRValue;
    return cg.builder.CreateExtractElement(vec, i);
}

Value* LgsIterIndex::loadFromSArray(LgsLLVMGen& cg) const {
    std::vector<Value*> IRIndices;
    Type* ty = nullptr;
    Value* ptr = nullptr;
    auto iterIndex = this;
    while (true) {
        auto irValue = iterIndex->index.from->IRValue;
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
    const auto gep = cg.builder.CreateGEP(ty, ptr, IRIndices);
    return cg.builder.CreateLoad(type->getIRType(cg), gep);
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
        putFunc.callIR(cg, {baseIRValue->IRValue, index.from->IRValue, ptr});
        return;
    }
    if (baseExpr->type->asSArray()) {
        cg.builder.CreateStore(rIRValue, loadFromSArray(cg));
        return;
    }
    if (const auto map = baseExpr->type->asMap()) {
        map->getAddFunc()->call(cg, {baseExpr, index.from, expr});
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
    if (index.to) {
        str << '[' << index.from->pname() << ':' << index.to->pname() << ']';
    } else {
        str << '[' << index.from->pname() << ']';
    }
    return str.str();
}

json::value LgsIterIndex::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "iterIndex";
    jsonObj["from"] = index.from->asJSON();
    if (index.to) jsonObj["to"] = index.to->asJSON();
    jsonObj["baseExpr"] = baseExpr->asJSON();
    return jsonObj;
}

LgsIterIndex::~LgsIterIndex() {
    if (!baseExpr->asVariable()) {
        freeExpr(baseExpr);
    }
    freeExpr(index.from);
    freeExpr(index.to);
    baseExpr = nullptr;
    index.from = nullptr;
    index.to = nullptr;
}
