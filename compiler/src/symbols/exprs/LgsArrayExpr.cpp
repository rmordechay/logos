#include "exprs/LgsArrayExpr.h"
#include "types/iterables/LgsSet.h"
#include "LgsUtils.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    if (type->asDArray() || type->asSet()) return IRValue;
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

Value* LgsArrayExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    if (const auto sArr = type->asSArray()) {
        if (toType->asStr() && sArr->baseType->asChar()) {
            return IRValue;
        }
    }
    return IRValue;
}

void LgsArrayExpr::castImplicitly(LgsType* toType) {
    // Replace static and dynamic if needed
    if (!type && toType->asSArray()) {
        setType(toType->clone());
    } else if (type->asDArray() && (toType->asSArray() || toType->asSet())) {
        freeType(type);
        setType(toType->clone());
    }

    LgsType* otherBaseType = nullptr;
    if (toType->asSet()) {
        otherBaseType = toType->genericArgs.front();
    } else {
        otherBaseType = toType->asIterable()->baseType;
    }
    for (size_t i = 0; i < elements.size(); ++i) {
        if (elements[i]->type) continue;
        elements[i]->castImplicitly(otherBaseType->clone());
    }
    type->asIterable()->baseType = otherBaseType->clone();
}

void LgsArrayExpr::setDebugValue(LgsLLVMGen& cg) {
    if (!IRValue) return;
    const auto di = cg.debugger.diBuilder;
    const auto file = cg.debugger.diFile;

    llvm::DIType* dbType = nullptr;
    if (const auto sarr = type->asSArray()) {
        dbType = sarr->getDebugType(cg);
    } else if (const auto darr = type->asDArray()) {
        dbType = darr->getDebugType(cg);
    } else if (const auto sett = type->asSet()) {
        dbType = sett->getDebugType(cg);
    } else {
        assert(0);
    }
    const auto var = di->createAutoVariable(cg.debugger.subprogram, "", file, location.lineStart, dbType);
    di->insertDeclare(IRValue, var, di->createExpression(), cg.getDebugLoc(location), cg.builder.GetInsertBlock());
}

std::string LgsArrayExpr::asText() {
    return type ? type->pname() : "[]";
}

LgsExpr* LgsArrayExpr::clone() {
    const auto newArr = new LgsArrayExpr(*this);
    newArr->type = type->clone();
    newArr->elements.clear();
    for (const auto element : elements) {
        newArr->elements.push_back(element->clone());
    }
    return newArr;
}

LgsArrayExpr::~LgsArrayExpr() {
    for (const auto& initialElement : elements) {
        freeExpr(initialElement);
    }
    elements.clear();
}
