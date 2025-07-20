#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include "exprs/unary/LgsIterIndex.h"
#include "logos/LgsConfig.h"

string LgsArrayExpr::prettyName() {
    return type->prettyName();
}

Value* LgsArrayExpr::createIRValue(LgsModule* module) {
    if (type->asArray()->isStatic) return createConstArray(module);
    return createDynamicArray(module);
}

Value* LgsArrayExpr::createDynamicArray(LgsModule* module) const {
    assert(0);
}

Value* LgsArrayExpr::createConstArray(LgsModule* module) const {
    auto& builder = module->builder;
    const auto arr = type->asArray();
    const auto baseType = arr->baseType;
    const auto baseIRType = baseType->getIRType(module->context);
    const auto arrIRType = ArrayType::get(baseIRType, arr->iterLen);
    const auto arrIRPtr = builder.CreateAlloca(arrIRType);
    if (elements.empty()) return arrIRPtr;
    const auto arrSize = elements.size();
    const auto type = ArrayType::get(baseIRType, arrSize);
    if (elementsAreStatic) {
        const auto value = createIRConstArray(module, elements);
        const auto globalVarIR = createIRGlobal(module, type, value);
        const auto iterBytesSize = dataLayout.getTypeAllocSize(baseType->getIRType(module->context)).getFixedValue() * arrSize;
        copyMem(module, globalVarIR, arrIRPtr, iterBytesSize);
    } else {
        for (int i = 0; i < elements.size(); ++i) {
            const auto gep = builder.CreateGEP(arrIRType, arrIRPtr, {builder.getInt32(0), builder.getInt32(i)});
            const auto val = elements[i]->getIRValue(module);
            builder.CreateStore(val, gep);
        }
    }
    return arrIRPtr;
}

Constant* LgsArrayExpr::createIRConstArray(LgsModule* module, const vector<LgsExpr*>& elements) const {
    const auto baseType = type->asArray()->baseType;
    const auto arrIRType = ArrayType::get(baseType->getIRType(module->context), elements.size());
    vector<Constant*> values;
    for (const auto element : elements) {
        if (const auto subArray = element->asArrayExpr()) {
            auto nested = createIRConstArray(module, subArray->elements);
            values.push_back(nested);
        } else {
            const auto val = element->getIRValue(module);
            assert(element->isStatic);
            values.push_back(cast<Constant>(val));
        }
    }
    return ConstantArray::get(arrIRType, values);
}

void LgsArrayExpr::free(LgsModule* module) {
    if (!type->asArray()->isStatic) {
        type->asArray()->freeFunc.call(module, {this});
    }
}
