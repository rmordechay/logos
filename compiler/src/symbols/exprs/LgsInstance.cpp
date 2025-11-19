#include "exprs/LgsInstance.h"
#include "exprs/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "LgsUtils.h"

std::string LgsInstance::asText() {
    return name + "{}";
}

LgsExpr* LgsInstance::castExplicitly(LgsType* toType) {
    assert(0);
}

Value* LgsInstance::castIR(LgsLLVMGen& cg, LgsType* toType) {
    return IRValue;
}

Value* LgsInstance::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsInstance::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, name);
    for (auto [argName, arg] : args) {
        hashNodeString(oldHash, argName);
        arg.expr->hashNode(oldHash);
    }
}

void LgsInstance::setObject(LgsObject* newObj) {
    obj = newObj;
    setType(obj);
}

bool LgsInstance::equals(LgsExpr* other) {
    const auto otherInstance = other->asInstance();
    if (!otherInstance) return false;
    assert(0);
}

LgsInstance::~LgsInstance() {
    for (const auto& [_, arg] : args) {
        freeExpr(arg.expr);
    }
    args.clear();
    freeType(obj);
    obj = nullptr;
    setType(nullptr);
}
