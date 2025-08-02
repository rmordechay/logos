#include "extern/LgsCLangVisitor.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "files/LgsFile.h"
#include "stmts/LgsField.h"
#include "types/LgsDArray.h"
#include "types/LgsObject.h"
#include "types/LgsCPtr.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"
#include "types/LgsVoid.h"

bool isCharPointer(const clang::QualType qt) {
    if (!qt->isPointerType()) return false;
    const auto pointeeType = qt->getPointeeType();
    return pointeeType->isCharType();
}

bool LgsCLangVisitor::VisitFunctionDecl(const clang::FunctionDecl* func) {
    auto name = func->getNameAsString();
    if (isLogosKeyword(name)) {
        name = name + '_';
    }
    const auto lgsType = mapCType(func->getReturnType());
    const auto funcImpl = new LgsFunc(name, lgsType);
    for (int i = 0; i < func->getNumParams(); ++i) {
        const auto paramType = func->getParamDecl(i)->getType();
        const auto lgsParam = LgsParam(mapCType(paramType));
        funcImpl->funcType->params.push_back(lgsParam);
    }
    funcImpl->funcType->isVariadic = func->isVariadic();
    cFile->symbolTable.addSymbol(name, LgsSymbol(funcImpl, true), nullptr);
    return true;
}

bool LgsCLangVisitor::VisitRecordDecl(const clang::RecordDecl* record) {
    auto name = record->getNameAsString();
    if (!name.empty() && name[0] == '_') return true;
    if (isLogosKeyword(name)) {
        name = name + '_';
    }
    if (!record->isStruct() || !record->isThisDeclarationADefinition()) return true;
    const auto objSymbol = cFile->symbolTable.getSymbol(name);
    if (objSymbol) return true;
    const auto obj = mapCRecord(record);
    cFile->symbolTable.addSymbol(name, LgsSymbol(obj, true), nullptr);
    return true;
}

LgsType* LgsCLangVisitor::mapCType(const clang::QualType type) {
    if (isCharPointer(type)) {
        return new LgsStr();
    }
    if (type->isPointerType()) {
        return new LgsCPtr(mapCType(type->getPointeeType()));
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Bool)) {
        return new LgsBool();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Char_S)) {
        return new LgsChar();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::UChar)) {
        return new LgsChar();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Short)) {
        return new LgsShort();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::UShort)) {
        return new LgsShort();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Int)) {
        return new LgsInt();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::UInt)) {
        return new LgsUInt();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Long)) {
        return new LgsLong();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::ULong)) {
        return new LgsLong();
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Float)) {
        return new LgsFloat();
    }
    if (type->isVoidType()) {
        return new LgsVoid();
    }
    if (type->isStructureType()) {
        return mapCStruct(type);
    }
    if (type->isFunctionProtoType()) {
        return mapCFunc(type)->asFuncType();
    }
    if (type->isConstantArrayType()) {
        return mapCArray(type);
    }
    if (type->isConstantSizeType()) {
        return new LgsLong();
    }
    const auto typeStr = type.getAsString();
    if (typeStr == "fpos_t") {
        return new LgsLong();
    }
    errs() << "Unhandled type: " << typeStr << "\n";
    assert(0);
}

LgsObject* LgsCLangVisitor::mapCRecord(const clang::RecordDecl* record) {
    const auto name = record->getNameAsString();
    auto* obj = new LgsObject(name);
    for (const clang::FieldDecl* field : record->fields()) {
        const auto fieldName = field->getNameAsString();
        const auto fieldType = mapCType(field->getType());
        const auto lgsField = new LgsField(fieldName, &obj->name, fieldType);
        obj->fields[fieldName] = lgsField;
    }
    return obj;
}

LgsType* LgsCLangVisitor::mapCStruct(const clang::QualType type) {
    const auto recordType = type->getAsStructureType();
    const auto decl = recordType->getDecl();
    auto name = decl->getNameAsString();
    if (name == "") {
        name = decl->getQualifiedNameAsString();
    }
    const auto objSymbol = cFile->symbolTable.getSymbol(name);
    if (objSymbol) return objSymbol->object;
    const auto obj = mapCRecord(decl);
    cFile->symbolTable.addSymbol(name, LgsSymbol(obj, true), nullptr);
    return obj;
}

LgsType* LgsCLangVisitor::mapCFunc(const clang::QualType type) {
    const auto lgsFuncType = new LgsFuncType();
    const auto cFuncType = type->getAs<clang::FunctionProtoType>();
    lgsFuncType->rt = mapCType(cFuncType->getReturnType());
    for (const clang::QualType param : cFuncType->getParamTypes()) {
        auto lgsParam = LgsParam(mapCType(param));
        lgsFuncType->params.push_back(lgsParam);
    }
    return lgsFuncType;
}

LgsType* LgsCLangVisitor::mapCArray(const clang::QualType type) {
    const auto arrayType = cast<clang::ConstantArrayType>(type.getTypePtr());
    const auto baseType = mapCType(arrayType->getElementType());
    const auto size = arrayType->getSize().getZExtValue();
    const auto arr = new LgsDArray(baseType);
    arr->sizeExpr = new LgsIntConst(size);
    return arr;
}

void LgsCLangASTConsumer::HandleTranslationUnit(clang::ASTContext& context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
    lock_guard lock(mtx);
    externalFiles[visitor.cFile->name] = visitor.cFile;
}
