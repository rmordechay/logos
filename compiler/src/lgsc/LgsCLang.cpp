#include "lgsc/LgsCLang.h"
#include "LgsDefinitions.h"
#include "files/LgsFile.h"
#include "lgsc/LgsCLangParser.h"
#include "LgsConfigs.h"
#include "LgsUtils.h"
#include <iostream>
#include <clang/Driver/Driver.h>
#include <llvm/TargetParser/Host.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/SourceManager.h>
#include <llvm/Support/MemoryBuffer.h>

using namespace clang;

bool LgsCLang::parseFile(LgsCLangParser& parser, const std::string& cCode) const {
    CompilerInstance compiler;
    auto diagConsumer = std::make_unique<LgsDiagnosticConsumer>();
    compiler.createDiagnostics(diagConsumer.release());
    compiler.getInvocation().getTargetOpts().Triple = llvm::sys::getDefaultTargetTriple();
    compiler.getHeaderSearchOpts().AddPath(cLibHeadersDir.c_str(), frontend::System, false, false);
    const auto targetOptions = std::make_shared<TargetOptions>(compiler.getInvocation().getTargetOpts());
    compiler.setTarget(TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), targetOptions));
    compiler.createFileManager();
    compiler.createSourceManager(compiler.getFileManager());

    auto buffer = llvm::MemoryBuffer::getMemBuffer(cCode);
    const auto fileID = compiler.getSourceManager().createFileID(std::move(buffer));
    compiler.getSourceManager().setMainFileID(fileID);
    compiler.createPreprocessor(TU_Complete);
    compiler.getPreprocessorOpts().UsePredefines = true;
    compiler.getPreprocessor().addPPCallbacks(std::make_unique<LgsPPCallbacks>(compiler.getLangOpts(), compiler.getSourceManager()));
    compiler.createASTContext();
    if (compiler.getDiagnostics().hasErrorOccurred()) return false;
    ParseAST(compiler.getPreprocessor(), &parser, compiler.getASTContext());
    if (compiler.getDiagnostics().hasErrorOccurred()) return false;
    return true;
}

void LgsPPCallbacks::MacroDefined(const Token& macroNameToken, const MacroDirective* macroDirective) {
    const auto stringRef = macroNameToken.getIdentifierInfo()->getName();
    if (stringRef.starts_with("SEEK")) {
        const auto macroInfo = macroDirective->getMacroInfo();
        if (!macroInfo) return;
        const auto name = macroNameToken.getIdentifierInfo()->getName().str();
        std::string value;
        for (unsigned i = 0; i < macroInfo->getNumTokens(); ++i) {
            const Token &tok = macroInfo->getReplacementToken(i);
            value += Lexer::getSpelling(tok, sourceManager, LangOpts);
            value += " ";
        }
        std::cout << value << '\n';
    }
}

void LgsDiagnosticConsumer::HandleDiagnostic(const DiagnosticsEngine::Level level, const Diagnostic& info) {
    SmallString<128> message;
    info.FormatDiagnostic(message);
    std::stringstream msg;
    switch (level) {
    case DiagnosticsEngine::Error:
    case DiagnosticsEngine::Fatal: {
        SourceLocation loc = info.getLocation();
        if (loc.isValid()) {
            const auto &SM = info.getSourceManager();
            PresumedLoc PLoc = SM.getPresumedLoc(loc);
            if (PLoc.isValid()) {
                const auto b = std::string(PLoc.getFilename()) + ':' + std::to_string(PLoc.getLine()) + ':' +  std::to_string(PLoc.getColumn());
                const auto a = message.str().str();
                std::cout << a << '\n';
                std::cout << b << '\n';
            }
        }
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
