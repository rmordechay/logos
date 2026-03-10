#include "lgsc/LgsCCompiler.h"

#include <clang/Lex/Preprocessor.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/ADT/SmallString.h>
#include <llvm/ADT/StringRef.h>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "lgsc/LgsCCParser.h"
#include "LgsConfigs.h"
#include "LgsUtils.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/CompilerInstance.h"

using namespace clang;

bool LgsCCompiler::parseFile(const fs::path& headerPath) {
    std::string includePath = paths.cLibHeadersDir;
    auto filePath = includePath / headerPath;
    std::string code = "";
    if (fs::exists(filePath)) {
        code = getFileText(filePath);
    } else {
        for (const auto& userCLib : paths.userSearchPaths) {
            includePath = userCLib;
            filePath = includePath / headerPath;
            if (fs::exists(filePath)) {
                code = getFileText(filePath);
                break;
            }
        }
    }
    if (code == "") return false;
    std::vector<std::string> args = {
        "-w", "-xc",
        "-I" + std::string(paths.cLibHeadersDir),
    };
    if (includePath != paths.cLibHeadersDir) {
        args.push_back("-I" + includePath);
    }
    return tooling::runToolOnCodeWithArgs(std::make_unique<LgsParseAction>(parser), code, args);
}

std::unique_ptr<ASTConsumer> LgsParseAction::CreateASTConsumer(CompilerInstance& ci, StringRef inFile) {
    auto ppCallbacks = std::make_unique<LgsPPCallbacks>(parser.symbolTable, ci);
    ci.getPreprocessor().addPPCallbacks(std::move(ppCallbacks));
    return std::make_unique<LgsCCAstConsumer>(parser);
}

void LgsDiagnosticConsumer::HandleDiagnostic(const DiagnosticsEngine::Level level, const Diagnostic& info) {
    SmallString<128> message;
    info.FormatDiagnostic(message);
    std::stringstream msg;
    switch (level) {
    case DiagnosticsEngine::Error:
    case DiagnosticsEngine::Fatal: {
        logError(message.str().str() + "\n");
        break;
    }
    case DiagnosticsEngine::Warning:
        if (lgsConfigs.isDevMode) logWarning(message.str().str() + "\n");
        break;
    default:
        break;
    }
}
