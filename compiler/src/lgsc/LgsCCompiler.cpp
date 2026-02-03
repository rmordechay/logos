#include "lgsc/LgsCCompiler.h"
#include "LgsDefinitions.h"
#include "lgsc/LgsCLangParser.h"
#include "LgsConfigs.h"
#include "LgsUtils.h"
#include "stmts/LgsVarDec.h"
#include <clang/Driver/Driver.h>
#include <llvm/TargetParser/Host.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/SourceManager.h>

#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsInt.h"

using namespace clang;

void LgsCCompiler::initCompiler() {
    auto diagConsumer = std::make_unique<LgsDiagnosticConsumer>();
    compiler.createDiagnostics(*vfs::getRealFileSystem());
    clang::TargetOptions& targetOpts = compiler.getInvocation().getTargetOpts();
    auto& headerSearchOptions = compiler.getHeaderSearchOpts();

    targetOpts.Triple = sys::getDefaultTargetTriple();
    headerSearchOptions.UseBuiltinIncludes = true;
    headerSearchOptions.UseStandardSystemIncludes = true;

    const auto cLibHeader = paths.cLibHeadersDir.c_str();
    headerSearchOptions.ResourceDir = cLibHeader;
    headerSearchOptions.AddPath(cLibHeader, frontend::System, false, false);
    for (auto searchPath : paths.userSearchPaths) {
        if (!fs::exists(searchPath)) continue;
        headerSearchOptions.AddPath(fs::canonical(searchPath).c_str(), frontend::Quoted, false, false);
    }

    const auto targetOptions = std::make_shared<clang::TargetOptions>(targetOpts);
    compiler.setTarget(TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), *targetOptions));
    compiler.createFileManager();
    compiler.createSourceManager(compiler.getFileManager());
}

bool LgsCCompiler::parseFile(const fs::path& headerPath) {
    compiler.getPreprocessorOpts().UsePredefines = true;
    compiler.createPreprocessor(TU_Complete);

    auto& pp = compiler.getPreprocessor();
    auto& si = pp.getHeaderSearchInfo();
    const ConstSearchDirIterator fromDir = {nullptr};
    ConstSearchDirIterator *curDir = nullptr;
    constexpr ArrayRef<std::pair<OptionalFileEntryRef, DirectoryEntryRef>> includers;
    auto file = si.LookupFile(
        headerPath.string(), SourceLocation(), false, fromDir, curDir, includers,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
    );
    if (!file.has_value()) return false;

    const auto fileCharacter = fs::exists(paths.cLibHeadersDir / headerPath) ? SrcMgr::C_System : SrcMgr::C_User;
    const auto fileID = compiler.getSourceManager().createFileID(*file, SourceLocation(), fileCharacter);
    compiler.getSourceManager().setMainFileID(fileID);
    auto ppCallback = std::make_unique<LgsPPCallbacks>(parser.symbolTable, pp, compiler.getLangOpts(), compiler.getSourceManager());
    pp.addPPCallbacks(std::move(ppCallback));

    compiler.createASTContext();
    if (compiler.getDiagnostics().hasErrorOccurred()) return false;
    ParseAST(pp, &parser, compiler.getASTContext());
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
        if (!symbolTable.symbols.contains(varDec->name)) {
            symbolTable.addSymbol(LgsSymbol(varDec, false, true), &errHandler);
        }
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
