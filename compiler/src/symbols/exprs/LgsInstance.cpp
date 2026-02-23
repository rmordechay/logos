#include "exprs/LgsInstance.h"

#include <assert.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <utility>

#include "LgsRTTIndices.h"
#include "stmts/LgsField.h"
#include "LgsUtils.h"
#include "codegen/LgsCodeGen.h"
#include "LgsType.h"

namespace llvm {
class Type;
class Value;
}

LgsField* LgsInstance::getField(const std::string& fieldName) const {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    return nullptr;
}

void LgsInstance::setType(LgsType* newObj) {
    obj = newObj->asObject();
    type = newObj;
}

void LgsInstance::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, name);
    for (auto [argName, arg] : args) {
        hashNodeString(oldHash, argName);
        arg.expr->hashNode(oldHash);
    }
}

bool LgsInstance::equals(LgsExpr* other) {
    const auto otherInstance = other->asInstance();
    if (!other->asInstance()) return false;
    return name == otherInstance->name;
}

void LgsInstance::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsInstance::asText() {
    return name + "{}";
}

Value* LgsInstance::getInstanceRTType(LgsCodeGen& cg, Value* instance) {
    return cg.loadPtr(cg.builder.CreatePtrAdd(instance, cg.getTypeSize(cg.sizeTy())));
}

Value* LgsInstance::loadRTType(LgsCodeGen& cg, Type* ty, Value* ptr) {
    return cg.loadField(ty, ptr, LgsInstanceIndices::type, cg.ptrTy());
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
