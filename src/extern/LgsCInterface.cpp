#include "extern/LgsCInterface.h"
#include "types/LgsObject.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsVoid.h"
#include "types/LgsStr.h"

bool LgsCVisitor::VisitFunctionDecl(const clang::FunctionDecl* func) {
    if (!isValid(func->getLocation()) || !func->isThisDeclarationADefinition()) return true;
    const auto name = func->getNameAsString();
    const auto returnType = func->getReturnType();
    const auto lgsType = mapCType(returnType);
    const auto funcImpl = new LgsFunc(name, lgsType);
    for (int i = 0; i < func->getNumParams(); ++i) {
        const auto paramType = func->getParamDecl(i)->getType();
        const auto lgsParam = new LgsParam(mapCType(paramType));
        funcImpl->funcType.params.push_back(lgsParam);
    }
    globals.addSymbol(name, LgsSymbol(funcImpl), nullptr);
    return true;
}

bool LgsCVisitor::VisitRecordDecl(const clang::RecordDecl* record) {
    if (!isValid(record->getLocation())) return true;
    if (!record->isStruct() || !record->isThisDeclarationADefinition()) return true;
    const auto name = record->getNameAsString();
    const auto objSymbol = getSymbol(name);
    if (objSymbol) return true;
    const auto obj = createLgsObj(record);
    globals.addSymbol(name, LgsSymbol(obj), nullptr);
    return true;
}

LgsObject* LgsCVisitor::createLgsObj(const clang::RecordDecl* record) {
    const auto name = record->getNameAsString();
    auto* obj = new LgsObject(name);
    for (const clang::FieldDecl* field : record->fields()) {
        const auto fieldName = field->getNameAsString();
        const auto fieldType = mapCType(field->getType());
        const auto lgsField = new LgsField(fieldName, fieldType);
        lgsField->parent = obj;
        obj->fields[fieldName] = lgsField;
    }
    return obj;
}

LgsType* LgsCVisitor::mapCType(const clang::QualType type) {
    if (isConstCharPointer(type)) {
        return new LgsStr();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Char_S)) {
        return new LgsChar();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Int)) {
        return new LgsInt();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Float)) {
        return new LgsFloat();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Bool)) {
        return new LgsBool();
    }
    if (type->isVoidType()) {
        return new LgsVoid();
    }
    if (type->isPointerType()) {
        return mapCType(type->getPointeeType());
    }
    if (type->isStructureType()) {
        const auto recordType = type->getAsStructureType();
        const auto decl = recordType->getDecl();
        auto name = decl->getNameAsString();
        if (name == "") {
            name = decl->getQualifiedNameAsString();
        }
        const auto objSymbol = getSymbol(name);
        if (objSymbol) return objSymbol->object;
        const auto obj = createLgsObj(decl);
        globals.addSymbol(name, LgsSymbol(obj), nullptr);
        return obj;
    }
    assert(false);
}

LgsSymbol* LgsCVisitor::getSymbol(const string& name) const {
    LgsSymbol* symbol = nullptr;
    if (globals.symbols.find(name) != globals.symbols.end()) {
        symbol = &globals.symbols[name];
    }
    return symbol;
}

bool LgsCVisitor::isConstCharPointer(const clang::QualType qt) const {
    if (!qt->isPointerType()) return false;
    const auto pointeeType = qt->getPointeeType();
    return pointeeType.isConstQualified() && pointeeType->isCharType();
}

bool LgsCVisitor::isValid(const clang::SourceLocation loc) const {
    return context->getSourceManager().isWrittenInMainFile(loc);
}
