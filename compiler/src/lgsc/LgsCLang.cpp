#include "lgsc/LgsCLang.h"
#include "LgsDefinitions.h"
#include "files/LgsFile.h"
#include "lgsc/LgsCLangParser.h"
#include "LgsConfigs.h"
#include "LgsUtils.h"
#include "exprs/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include <iostream>
#include <clang/Driver/Driver.h>
#include <llvm/TargetParser/Host.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/SourceManager.h>

using namespace clang;

bool LgsCLang::parseFile(LgsCLangParser& parser, const fs::path& headerPath) const {
    CompilerInstance compiler;
    auto diagConsumer = std::make_unique<LgsDiagnosticConsumer>();
    compiler.createDiagnostics(diagConsumer.release());

    auto& targetOpts = compiler.getInvocation().getTargetOpts();
    targetOpts.Triple = llvm::sys::getDefaultTargetTriple();
    compiler.getHeaderSearchOpts().UseBuiltinIncludes = true;
    compiler.getHeaderSearchOpts().UseStandardSystemIncludes = true;
    compiler.getHeaderSearchOpts().ResourceDir = cLibHeadersDir.c_str();
    compiler.getHeaderSearchOpts().AddPath(cLibHeadersDir.c_str(), frontend::System, false, false);

    const auto targetOptions = std::make_shared<TargetOptions>(targetOpts);
    compiler.setTarget(TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), targetOptions));
    compiler.createFileManager();
    compiler.createSourceManager(compiler.getFileManager());

    const auto fullPath = fs::absolute(cLibHeadersDir / headerPath).string();
    auto fileEntry = compiler.getFileManager().getFileRef(fullPath);
    if (!fileEntry) return false;
    const auto fileID = compiler.getSourceManager().createFileID(*fileEntry, SourceLocation(), SrcMgr::C_System);
    compiler.getSourceManager().setMainFileID(fileID);

    compiler.getPreprocessorOpts().UsePredefines = true;
    compiler.createPreprocessor(TU_Complete);
    auto& preprocessor = compiler.getPreprocessor();
    auto ppCallback = std::make_unique<LgsPPCallbacks>(parser.table, preprocessor, compiler.getLangOpts(), compiler.getSourceManager());
    preprocessor.addPPCallbacks(std::move(ppCallback));

    compiler.createASTContext();
    if (compiler.getDiagnostics().hasErrorOccurred()) return false;
    ParseAST(preprocessor, &parser, compiler.getASTContext());
    return !compiler.getDiagnostics().hasErrorOccurred();
}


void LgsPPCallbacks::MacroDefined(const Token& macroNameToken, const MacroDirective* macroDirective) {
    const auto stringRef = macroNameToken.getIdentifierInfo()->getName();
    const auto macroInfo = macroDirective->getMacroInfo();
    if (!macroInfo) return;
    const auto name = macroNameToken.getIdentifierInfo()->getName().str();
    std::string value;
    for (unsigned i = 0; i < macroInfo->getNumTokens(); ++i) {
        const auto& tok = macroInfo->getReplacementToken(i);
        value += Lexer::getSpelling(tok, sourceManager, LangOpts);
    }
    if (stringRef.starts_with("_")) return;
    if (value.length() == 1 && isdigit(value.front())) {
        const auto expr = new LgsIntConst(&LGS_INT, std::atoi(value.c_str()));
        const auto varDec = new LgsVarDec(stringRef.str(), expr);
        varDec->type = varDec->expr->type;
        table.addSymbol(LgsSymbol(varDec, false, true), &errHandler);
    }
}

void LgsDiagnosticConsumer::HandleDiagnostic(const DiagnosticsEngine::Level level, const Diagnostic& info) {
    SmallString<128> message;
    info.FormatDiagnostic(message);
    std::stringstream msg;
    switch (level) {
    case DiagnosticsEngine::Error:
    case DiagnosticsEngine::Fatal: {
        msg << message.str().str() << "\n";
        break;
    }
    case DiagnosticsEngine::Warning:
        if (lgsConfigs.isDevMode) logWarning(message.str().str() + "\n");
        break;
    default:
        break;
    }
}
