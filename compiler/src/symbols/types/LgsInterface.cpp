#include "types/LgsInterface.h"
#include "codegen/LgsCgModule.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

Type* LgsInterface::getIRType(LgsCgModule& cg) {
    return cg.ptrTy();
}

LgsFunc* LgsInterface::getMethod(const std::string& methodName) {
    const auto method = methods.find(methodName);
    if (method != methods.end() && method->second) {
        return method->second;
    }
    for (const auto* f : fields) {
        if (f->name != methodName) continue;
        if (f->expr && f->expr->asFunc()) {
            return f->expr->asFunc();
        }
    }
    return nullptr;
}

std::string LgsInterface::getName() {
    return name;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(0);
}

bool LgsInterface::canCastTo(LgsType* other) {
    if (const auto interface = other->asInterface()) {
        if (interface->name == getName()) return true;
    } else if (const auto obj = other->asObject()) {
        if (obj->name == getName()) return true;
        for (const auto& implement : obj->implements) {
            if (implement->getName() == getName()) return true;
        }
    }
    return false;
}

LgsType* LgsInterface::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

size_t LgsInterface::sizeBytes() {
    return 0;
}

DIType* LgsInterface::getDebugType(LgsCgModule& cg) {
    assert(0);
}

Constant* LgsInterface::getRTType(LgsCgModule& cg) {
    const auto objName = getName();
    std::vector<LgsValue*> fieldsAsValue;
    for (const auto field : fields) {
        fieldsAsValue.push_back(field);
    }
    const auto [typesArr, hashesArr] = getRTValuesInfo(cg, name, fieldsAsValue);
    // name, fieldsCount, fieldNames, fieldTypes
    const std::vector<Type*> params = {cg.ptrTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Constant*> args = {llvm::dyn_cast<Constant>(cg.getString(objName)), cg.usize(fields.size()), hashesArr, typesArr};
    const auto sv = cg.getRTTExtraStruct(objName, params, args);
    return cg.getRTTypeInfo(objName, sizeBytes(), RTT_OBJECT, sv);
}

std::string LgsInterface::fmtStr() const {
    assert(0);
}
