#include "lgsc/LgsCCParser.h"

#include <_ctype.h>
#include <_stdlib.h>
#include <assert.h>
#include <ostream>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Type.h>
#include <clang/Basic/IdentifierTable.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Lexer.h>
#include <clang/Lex/MacroInfo.h>
#include <clang/Lex/Token.h>
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "LgsTokens.h"
#include "exprs/constants/LgsIntConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"
#include "types/LgsCPtr.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"
#include "types/primitives/LgsVoid.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsSubType.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsAny.h"
#include "types/primitives/LgsLong.h"
#include "LgsSymbol.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsFuncType.h"
#include "types/primitives/LgsSize.h"

void LgsCCAstConsumer::HandleTranslationUnit(clang::ASTContext& clangContext) {
    parser.TraverseDecl(clangContext.getTranslationUnitDecl());
}

bool LgsCCParser::VisitFunctionDecl(clang::FunctionDecl* func) {
    auto name = func->getNameAsString();
    if (name == "LLVMVerifyModule") {
        printf("");
    }
    if (LGS_KEYWORDS.contains(name)) {
        name = name + '_';
    }
    const auto lgsType = mapCType(func->getReturnType());
    const auto funcImpl = new LgsFunc(name, lgsType);
    for (size_t i = 0; i < func->getNumParams(); ++i) {
        const auto paramDecl = func->getParamDecl(i);
        const auto paramType = paramDecl->getType();
        auto lgsParam = LgsParam(mapCType(paramType), paramDecl->getName().str());
        funcImpl->funcType->params.push_back(lgsParam);
    }
    funcImpl->funcType->isVariadic = func->isVariadic();
    funcImpl->funcType->isExternal = true;
    if (!name.empty() && !name.starts_with("_") && !symbolTable.symbols.contains(name)) {
        symbolTable.addSymbol(LgsSymbol(funcImpl, false, true), &errHandler);
    }
    return true;
}

bool LgsCCParser::VisitRecordDecl(const clang::RecordDecl* record) {
    auto name = record->getNameAsString();
    if (name.empty()) return true;
    if (LGS_KEYWORDS.contains(name)) name = name + '_';
    const auto objSymbol = symbolTable.getSymbol(name);
    if (objSymbol) return true;
    symbolTable.addSymbol(LgsSymbol(mapCRecord(record), false, true), &errHandler);
    return true;
}

bool LgsCCParser::VisitTypedefDecl(const clang::TypedefDecl* typedefDecl) {
    const auto typedefName = typedefDecl->getNameAsString();
    const auto underlyingType = typedefDecl->getUnderlyingType();
    const auto cType = mapCType(underlyingType);
    const auto subtype = new LgsSubType(typedefName, cType);
    cType->isExternal = true;
    subtype->isExternal = true;
    symbolTable.addSymbol(LgsSymbol(subtype, true), &errHandler);
    return true;
}

LgsType* LgsCCParser::mapCType(const clang::QualType type) {
    if (recursionDepth++ > 100000) assert(0);
    if (type->isPointerType() && type->getPointeeType()->isCharType()) {
        return new LgsStr();
    }
    if (type->isPointerType()) {
        const auto pointee = type->getPointeeType();
        if (pointee->isVoidType() || pointee->isElaboratedTypeSpecifier()) {
            return &LGS_ANY;
        }
        return new LgsCPtr(mapCType(pointee));
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Bool)) {
        return &LGS_BOOL;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Char_S)) {
        return &LGS_CHAR;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::UChar)) {
        return &LGS_CHAR;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Short)) {
        return &LGS_SHORT;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::UShort)) {
        return &LGS_SHORT;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Int)) {
        return &LGS_INT;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::UInt)) {
        return &LGS_UINT;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Long)) {
        return &LGS_LONG;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::ULong)) {
        return &LGS_LONG;
    }
    if (type->isSpecificBuiltinType(clang::BuiltinType::Float)) {
        return &LGS_FLOAT;
    }
    if (type->isVoidType()) {
        return &LGS_VOID;
    }
    if (type->isConstantSizeType()) {
        return &LGS_SIZE;
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
    errs() << "Unhandled type: " << type.getAsString() << "\n";
    assert(0);
}

LgsObject* LgsCCParser::mapCRecord(const clang::RecordDecl* record) {
    const auto name = record->getNameAsString();
    const auto obj = new LgsObject(name);
    for (const clang::FieldDecl* field : record->fields()) {
        const auto fieldName = field->getNameAsString();
        const auto fieldType = mapCType(field->getType());
        const auto lgsField = new LgsField(fieldName, fieldType);
        obj->fields.push_back(lgsField);
    }
    obj->isExternal = true;
    return obj;
}

LgsType* LgsCCParser::mapCStruct(const clang::QualType type) {
    const auto recordType = type->getAsStructureType();
    const auto decl = recordType->getDecl();
    auto name = decl->getNameAsString();
    if (name == "") {
        name = decl->getQualifiedNameAsString();
    }
    const auto objSymbol = symbolTable.getSymbol(name);
    if (objSymbol) return objSymbol->object;
    const auto obj = mapCRecord(decl);
    obj->name = name;
    if (!name.empty() && !name.starts_with("_")) {
        symbolTable.addSymbol(LgsSymbol(obj, false, true), &errHandler);
    }
    return obj;
}

LgsType* LgsCCParser::mapCFunc(const clang::QualType type) {
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

LgsType* LgsCCParser::mapCArray(const clang::QualType type) {
    const auto arrayType = llvm::dyn_cast<clang::ConstantArrayType>(type.getTypePtr());
    if (!arrayType) return nullptr;
    const auto baseType = mapCType(arrayType->getElementType());
    const auto size = arrayType->getSize().getZExtValue();
    return new LgsSArray(baseType, new LgsIntConst(&LGS_INT, size));
}

void LgsPPCallbacks::MacroDefined(const clang::Token& macroNameToken, const clang::MacroDirective* macroDirective) {
    const auto macroInfo = macroDirective->getMacroInfo();
    if (!macroInfo) return;
    const auto name = macroNameToken.getIdentifierInfo()->getName().str();
    std::string value;
    for (unsigned i = 0; i < macroInfo->getNumTokens(); ++i) {
        const auto& tok = macroInfo->getReplacementToken(i);
        value += clang::Lexer::getSpelling(tok, compiler.getSourceManager(), compiler.getLangOpts(), nullptr);
    }
    if (name.starts_with("_")) return;
    if (value.length() == 1 && isdigit(value.front())) {
        const auto expr = new LgsIntConst(&LGS_INT, std::atoi(value.c_str()));
        const auto varDec = new LgsVarDec(name, expr);
        varDec->type = varDec->expr->type;
        if (!symbolTable.symbols.contains(varDec->name)) {
            symbolTable.addSymbol(LgsSymbol(varDec, false, true), &errHandler);
        }
    }
}