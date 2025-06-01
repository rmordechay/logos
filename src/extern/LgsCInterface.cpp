#include "extern/LgsCInterface.h"
#include "funcs/LgsFuncImpl.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsFloat.h"

bool LgsCVisitor::VisitFunctionDecl(const FunctionDecl* func) {
    if (!isValid(func->getLocation()) || !func->isThisDeclarationADefinition()) return true;
    const auto name = func->getNameAsString();
    const auto returnType = func->getReturnType();
    const auto lgsType = mapCType(returnType);
    const auto funcImpl = new LgsFuncImpl(name, lgsType);
    for (int i = 0; i < func->getNumParams(); ++i) {
        const auto paramType = func->getParamDecl(i)->getType();
        const auto lgsParam = new LgsParam(mapCType(paramType));
        funcImpl->funcType.params.push_back(lgsParam);
    }
    globals.addSymbol(name, LgsSymbol(funcImpl), nullptr);
    return true;
}

bool LgsCVisitor::VisitRecordDecl(const RecordDecl* record) {
    if (!isValid(record->getLocation())) return true;
    if (!record->isStruct() || !record->isThisDeclarationADefinition()) return true;
    const auto obj = createLgsObj(record);
    globals.addSymbol(record->getNameAsString(), LgsSymbol(obj), nullptr);
    return true;
}

void LgsCASTConsumer::HandleTranslationUnit(ASTContext& context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
}

std::unique_ptr<ASTConsumer> LgsCFrontendAction::CreateASTConsumer(CompilerInstance& compilerInstance, StringRef file) {
    return std::make_unique<LgsCASTConsumer>(&compilerInstance.getASTContext());
}

LgsObject* LgsCVisitor::createLgsObj(const RecordDecl* record) {
    const auto name = record->getNameAsString();
    auto* obj = new LgsObject(name);
    for (const FieldDecl* field : record->fields()) {
        const auto fieldName = field->getNameAsString();
        const auto fieldType = mapCType(field->getType());
        const auto lgsField = new LgsField(fieldName, fieldType);
        lgsField->parent = obj;
        obj->fields[fieldName] = lgsField;
    }
    return obj;
}

LgsType* LgsCVisitor::mapCType(const QualType type) {
    if (isConstCharPointer(type)) {
        return new LgsStr();
    }
    if (type->isSpecificBuiltinType(BuiltinType::Char_S)) {
        return new LgsChar();
    }
    if (type->isSpecificBuiltinType(BuiltinType::Int)) {
        return new LgsInt();
    }
    if (type->isSpecificBuiltinType(BuiltinType::Float)) {
        return new LgsFloat();
    }
    if (type->isSpecificBuiltinType(BuiltinType::Bool)) {
        return new LgsBool();
    }
    if (type->isVoidType()) {
        return new LgsVoid();
    }
    if (type->isPointerType()) {
        return mapCType(type->getPointeeType());
    }
    if (type->isStructureType()) {
        const RecordType* recordType = type->getAsStructureType();
        const RecordDecl* decl = recordType->getDecl();
        auto name = decl->getNameAsString();
        if (name == "") {
            name = decl->getQualifiedNameAsString();
        }
        assert(name != "");
        const auto obj = createLgsObj(decl);
        globals.addSymbol(name, LgsSymbol(obj), nullptr);
        return obj;
    }
    assert(false);
}

bool LgsCVisitor::isConstCharPointer(const QualType qt) const {
    if (!qt->isPointerType()) return false;
    const auto pointeeType = qt->getPointeeType();
    return pointeeType.isConstQualified() && pointeeType->isCharType();
}

bool LgsCVisitor::isValid(const SourceLocation loc) const {
    return context->getSourceManager().isWrittenInMainFile(loc);
}
