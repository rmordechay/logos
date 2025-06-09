#include "extern/LgsCLangVisitor.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsVoid.h"

bool LgsCLangVisitor::VisitFunctionDecl(const clang::FunctionDecl* func) {
    const auto name = func->getNameAsString();
    const auto returnType = func->getReturnType();
    const auto lgsType = mapCType(returnType);
    const auto funcImpl = new LgsFunc(name, lgsType);
    for (int i = 0; i < func->getNumParams(); ++i) {
        const auto paramType = func->getParamDecl(i)->getType();
        const auto lgsParam = LgsParam(mapCType(paramType));
        funcImpl->funcType.params.push_back(lgsParam);
    }
    globals.addSymbol(name, LgsSymbol(funcImpl), &errHandler);
    return true;
}

bool LgsCLangVisitor::VisitRecordDecl(const clang::RecordDecl* record) {
    if (!isValid(record->getLocation())) return true;
    if (!record->isStruct() || !record->isThisDeclarationADefinition()) return true;
    const auto name = record->getNameAsString();
    const auto objSymbol = globals.getSymbol(name);
    if (objSymbol) return true;
    const auto obj = mapCRecord(record);
    globals.addSymbol(name, LgsSymbol(obj), &errHandler);
    return true;
}

LgsType* LgsCLangVisitor::mapCType(const clang::QualType type) {
    if (isConstCharPointer(type)) {
        return new LgsStr();
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
        return new LgsInt();
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
    if (type->isConstantSizeType()) {
        return new LgsLong();
    }
    if (type->isPointerType()) {
        return mapCType(type->getPointeeType());
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
    const auto typeStr = type.getAsString();
    if (typeStr == "fpos_t") {
        return new LgsLong();
    }
    errs() << "Unhandled type: " << typeStr << "\n";
    assert(false);
}

LgsObject* LgsCLangVisitor::mapCRecord(const clang::RecordDecl* record) {
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

LgsType* LgsCLangVisitor::mapCStruct(const clang::QualType type) {
    const auto recordType = type->getAsStructureType();
    const auto decl = recordType->getDecl();
    auto name = decl->getNameAsString();
    if (name == "") {
        name = decl->getQualifiedNameAsString();
    }
    const auto objSymbol = globals.getSymbol(name);
    if (objSymbol) return objSymbol->object;
    const auto obj = mapCRecord(decl);
    globals.addSymbol(name, LgsSymbol(obj), &errHandler);
    return obj;
}

LgsType* LgsCLangVisitor::mapCFunc(const clang::QualType type) {
    const auto lgsFuncType = new LgsFuncType();
    const auto cFuncType = type->getAs<clang::FunctionProtoType>();
    lgsFuncType->rt = mapCType(cFuncType->getReturnType());
    for (const clang::QualType param : cFuncType->getParamTypes()) {
        auto lgsParam = LgsParam(mapCType(param));
        lgsFuncType->params.emplace_back(lgsParam);
    }
    return lgsFuncType;
}

LgsType* LgsCLangVisitor::mapCArray(const clang::QualType type) {
    const auto arrayType = cast<clang::ConstantArrayType>(type.getTypePtr());
    const auto baseType = mapCType(arrayType->getElementType());
    const auto size = arrayType->getSize().getZExtValue();
    const auto arr = new LgsArray(baseType);
    arr->sizeExpr = new LgsIntConst(size);
    arr->isStatic = true;
    return arr;
}

bool LgsCLangVisitor::isConstCharPointer(const clang::QualType qt) const {
    if (!qt->isPointerType()) return false;
    const auto pointeeType = qt->getPointeeType();
    return pointeeType.isConstQualified() && pointeeType->isCharType();
}

void LgsCLangASTConsumer::HandleTranslationUnit(clang::ASTContext& context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
}

bool LgsCLangVisitor::isValid(const clang::SourceLocation loc) const {
    return context->getSourceManager().isWrittenInMainFile(loc);
}
