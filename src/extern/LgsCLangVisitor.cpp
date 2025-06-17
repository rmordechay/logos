#include "extern/LgsCLangVisitor.h"

#include "data/LgsDefinitions.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "files/LgsFile.h"
#include "stmts/LgsField.h"
#include "types/LgsArray.h"
#include "types/LgsObject.h"
#include "types/LgsPtr.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"
#include "types/primitives/LgsVoid.h"

// define i32 @main() #0 {
//   %2 = alloca i64, align 8
//   %3 = call i64 @time(ptr noundef null)
//   store i64 %3, ptr %2, align 8
//   %4 = call ptr @ctime(ptr noundef %2)
//   %5 = call i32 (ptr, ...) @printf(ptr noundef @.str, ptr noundef %4)
//   ret i32 0
// }

bool LgsCLangVisitor::VisitFunctionDecl(const clang::FunctionDecl* func) {
    auto name = func->getNameAsString();
    if (name == "ctime") {
        std::cout << "" << std::endl;
    }
    if (isLgsKeyword(name)) {
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
    cFile->symbolTable.addSymbol(name, LgsSymbol(funcImpl, true));
    return true;
}

bool LgsCLangVisitor::VisitRecordDecl(const clang::RecordDecl* record) {
    auto name = record->getNameAsString();
    if (!name.empty() && name[0] == '_') return true;
    if (isLgsKeyword(name)) {
        name = name + '_';
    }
    if (!record->isStruct() || !record->isThisDeclarationADefinition()) return true;
    const auto objSymbol = cFile->symbolTable.getSymbol(name);
    if (objSymbol) return true;
    const auto obj = mapCRecord(record);
    cFile->symbolTable.addSymbol(name, LgsSymbol(obj, true));
    return true;
}

LgsType* LgsCLangVisitor::mapCType(const clang::QualType type) {
    if (isCharPointer(type)) {
        return new LgsStr();
    }
    if (type->isPointerType()) {
        return new LgsPtr(mapCType(type->getPointeeType()));
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
    cFile->symbolTable.addSymbol(name, LgsSymbol(obj, true));
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
    const auto arr = new LgsArray(baseType);
    arr->sizeExpr = new LgsIntConst(size);
    arr->isStatic = true;
    return arr;
}

bool LgsCLangVisitor::isCharPointer(const clang::QualType qt) const {
    if (!qt->isPointerType()) return false;
    const auto pointeeType = qt->getPointeeType();
    return pointeeType->isCharType();
}

bool LgsCLangVisitor::isLgsKeyword(const string& s) const {
    return LOGOS_KEYWORDS.find(s) != LOGOS_KEYWORDS.end();
}

void LgsCLangASTConsumer::HandleTranslationUnit(clang::ASTContext& context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
    lock_guard lock(mtx);
    externalFiles[visitor.cFile->name] = visitor.cFile;
}
