#include "exprs/LgsInstance.h"
#include "exprs/LgsHashMap.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"
#include "LgsUtils.h"

std::string LgsInstance::asText() {
    return name + "{}";
}

LgsExpr* LgsInstance::castExplicitly(LgsType* toType) {
    assert(0);
}

Value* LgsInstance::castIR(LgsCgModule& cg, LgsType* toType) {
    return IRValue;
}

Value* LgsInstance::loadIR(LgsCgModule& cg) {
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
    obj = nullptr;
    setType(nullptr);
}
