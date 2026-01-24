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

Value* LgsInstance::loadIR(LgsCodeGen& cg) {
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
    if (!other->asInstance()) return false;
    return name == otherInstance->name;
}

void LgsInstance::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsField* LgsInstance::getField(const std::string& fieldName) const {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    return nullptr;
}

LgsInstance::~LgsInstance() {
    for (const auto& [_, arg] : args) {
        freeExpr(arg.expr);
    }
    args.clear();
    for (const auto field : fields) {
        field->type = nullptr;
        delete field;
    }
    obj = nullptr;
    type = nullptr;
}
