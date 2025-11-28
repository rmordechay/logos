#include "lgsc/LgsCLangParser.h"
#include "exprs/constants/LgsIntConst.h"
#include "files/LgsFile.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsObject.h"
#include "types/LgsPtr.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"
#include "types/primitives/LgsVoid.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "LgsUtils.h"
#include "types/primitives/LgsLong.h"

#include <iostream>

void LgsCLangParser::HandleTranslationUnit(clang::ASTContext& clangContext){
    context = &clangContext;
    TraverseDecl(clangContext.getTranslationUnitDecl());
}

bool LgsCLangParser::VisitFunctionDecl(const clang::FunctionDecl* func) {
    auto name = func->getNameAsString();
    if (isLogosKeyword(name)) {
        name = name + '_';
    }
    const auto lgsType = mapCType(func->getReturnType());
    const auto funcImpl = new LgsFunc(name, lgsType);
    for (size_t i = 0; i < func->getNumParams(); ++i) {
        const auto paramDecl = func->getParamDecl(i);
        const auto paramType = paramDecl->getType();
        auto lgsParam = LgsParam(mapCType(paramType), paramDecl->getName().str());
        lgsParam.index = i;
        funcImpl->funcType->params.push_back(lgsParam);
    }
    funcImpl->funcType->isVariadic = func->isVariadic();
    funcImpl->funcType->isExternal = true;
    if (!name.starts_with("_")) {
        table.addSymbol(LgsSymbol(funcImpl, false, true), &errHandler);
    }
    return true;
}

bool LgsCLangParser::VisitRecordDecl(const clang::RecordDecl* record) {
    auto name = record->getNameAsString();
    if (!name.empty() && name[0] == '_') return true;
    if (isLogosKeyword(name)) {
        name = name + '_';
    }
    if (!record->isStruct() || !record->isThisDeclarationADefinition()) return true;
    const auto objSymbol = table.getSymbol(name);
    if (objSymbol) return true;
    const auto obj = mapCRecord(record);
    if (!name.starts_with("_")) {
        table.addSymbol(LgsSymbol(obj, false, true), &errHandler);
    }
    return true;
}

LgsType* LgsCLangParser::mapCType(const clang::QualType type) {
    if (recursionDepth++ > 100000) assert(0);
    if (type->isPointerType() && type->getPointeeType()->isCharType()) {
        return new LgsStr();
    }
    if (type->isPointerType()) {
        const auto pointee = type->getPointeeType();
        if (pointee.getTypePtr() == type.getTypePtr()) {
            return new LgsPtr(new LgsVoid());
        }
        if (pointee.getTypePtr() == type.getTypePtr()) {
            return new LgsPtr(new LgsVoid());
        }
        if (pointee->isVoidType()) {
            return new LgsPtr(new LgsVoid());
        }
        if (pointee->isIncompleteType() && !pointee->isStructureType()) {
            return new LgsPtr(new LgsVoid());
        }
        if (pointee->isElaboratedTypeSpecifier()) {
            return new LgsPtr(new LgsVoid());
        }
        if (std::string(pointee->getTypeClassName()) == "Elaborated") return new LgsPtr(new LgsVoid());;
        if (std::string(pointee->getTypeClassName()) == "Paren") return new LgsPtr(new LgsVoid());;
        return new LgsPtr(mapCType(pointee));
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
    llvm::errs() << "Unhandled type: " << typeStr << "\n";
    assert(0);
}

LgsObject* LgsCLangParser::mapCRecord(const clang::RecordDecl* record) {
    const auto name = record->getNameAsString();
    const auto obj = new LgsObject(name);
    for (const clang::FieldDecl* field : record->fields()) {
        const auto fieldName = field->getNameAsString();
        const auto fieldType = mapCType(field->getType());
        const auto lgsField = new LgsField(fieldName, fieldType);
        obj->addField(lgsField);
    }
    return obj;
}

LgsType* LgsCLangParser::mapCStruct(const clang::QualType type) {
    const auto recordType = type->getAsStructureType();
    const auto decl = recordType->getDecl();
    auto name = decl->getNameAsString();
    if (name == "") {
        name = decl->getQualifiedNameAsString();
    }
    const auto objSymbol = table.getSymbol(name);
    if (objSymbol) return objSymbol->object;
    const auto obj = mapCRecord(decl);
    if (!name.starts_with("_")) {
        table.addSymbol(LgsSymbol(obj, false, true), &errHandler);
    }
    return obj;
}

LgsType* LgsCLangParser::mapCFunc(const clang::QualType type) {
    const auto lgsFuncType = new LgsFuncType();
    lgsFuncType->isExternal = true;
    const auto cFuncType = type->getAs<clang::FunctionProtoType>();
    lgsFuncType->rt = mapCType(cFuncType->getReturnType());
    for (const clang::QualType param : cFuncType->getParamTypes()) {
        auto lgsParam = LgsParam(mapCType(param), param.getAsString());
        lgsFuncType->params.push_back(lgsParam);
    }
    return lgsFuncType;
}

LgsType* LgsCLangParser::mapCArray(const clang::QualType type) {
    const auto arrayType = llvm::dyn_cast<clang::ConstantArrayType>(type.getTypePtr());
    if (!arrayType) return nullptr;
    const auto baseType = mapCType(arrayType->getElementType());
    const auto size = arrayType->getSize().getZExtValue();
    const auto arr = new LgsDArray(baseType);
    arr->size = new LgsIntConst(&LGS_INT, size);
    return arr;
}
