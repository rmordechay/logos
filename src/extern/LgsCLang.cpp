#include "extern/LgsCLang.h"
#include "data/LgsErrors.h"
#include "extern/LgsCLangVisitor.h"
#include "logos/Platform.h"
#include "utils/LgsUtils.h"

using namespace clang;

void LgsCLang::parse() const {
    for (const auto filePath : lgsFile.externFiles) {
        auto path = filePath->value;
        string code;
        auto cLibPath = platform.clibRoot / "usr/include" / path;
        if (exists(cLibPath)) {
            code = getFileText(cLibPath);
        } else {
            assert(false);
        }
        if (code.empty()) {
            errHandler.handleError(E10047, &filePath->location, {path});
            continue;
        }
        runToolOnCodeWithArgs(std::make_unique<LgsCLangFeAction>(lgsFile, errHandler), code, {"-isysroot", platform.clibRoot});
    }
}

void LgsCLang::compile(const vector<string>& files) {
    if (files.empty()) return;
    for (const auto& file : files) {
        compileArgs.push_back(file);
    }
    compileArgs.push_back("-o");
    compileArgs.push_back(outputFilePath.string());

    vector<const char*> args;
    for (const auto& argStr : compileArgs) {
        args.push_back(argStr.c_str());
    }

    const auto targetTriple = sys::getDefaultTargetTriple();
    auto diags = CompilerInstance::createDiagnostics(*fs, new DiagnosticOptions, &dc, false);
    Driver driver(args[0], targetTriple, *diags, "cc", fs);
    driver.setCheckInputsExist(false);

    unique_ptr<Compilation> compilation(driver.BuildCompilation(args));
    const auto& jobs = compilation->getJobs();
    if (jobs.empty()) {
        return;
    }

    const auto& ccArgs = jobs.begin()->getArguments();
    auto invocation = make_unique<CompilerInvocation>();
    CompilerInvocation::CreateFromArgs(*invocation, ccArgs, *diags);
    LgsDiagnosticsConsumer diagnosticsConsumer;
    auto compilerInstance = make_unique<CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
    compilerInstance->createDiagnostics(*fs, &diagnosticsConsumer, false);
    compilerInstance->getDiagnostics().getDiagnosticOptions().ShowCarets = false;
    compilerInstance->createFileManager(fs);
    compilerInstance->createSourceManager(compilerInstance->getFileManager());
    compilerInstance->getCodeGenOpts().DisableFree = false;
    compilerInstance->getFrontendOpts().DisableFree = false;

    switch (compilerInstance->getFrontendOpts().ProgramAction) {
    case frontend::ActionKind::EmitObj: {
        EmitObjAction action;
        compilerInstance->ExecuteAction(action);
    }
    break;
    case frontend::ActionKind::EmitAssembly: {
        EmitAssemblyAction action;
        compilerInstance->ExecuteAction(action);
    }
    break;
    default: assert(false);
    }
}

void LgsDiagnosticsConsumer::HandleDiagnostic(const DiagnosticsEngine::Level diagLevel, const Diagnostic& info) {
    DiagnosticConsumer::HandleDiagnostic(diagLevel, info);
    const char* level;
    switch (diagLevel) {
    default:
        return;
    case DiagnosticsEngine::Note:
        level = "note";
        break;
    case DiagnosticsEngine::Warning:
        level = "warning";
        break;
    case DiagnosticsEngine::Error:
    case DiagnosticsEngine::Fatal:
        level = "error";
        break;
    }

    SmallString<256> msg;
    info.FormatDiagnostic(msg);
    if (info.hasSourceManager()) {
        const auto& sm = info.getSourceManager();
        auto loc = info.getLocation();
        const auto fileLoc = sm.getFileLoc(loc);
        os << sm.getFilename(fileLoc) << ':' << sm.getSpellingLineNumber(fileLoc) << ':' << sm.
            getSpellingColumnNumber(fileLoc) << ": " << level << ": " << msg << '\n';

        if (loc.isMacroID()) {
            loc = sm.getSpellingLoc(loc);
            os << sm.getFilename(loc) << ':' << sm.getSpellingLineNumber(loc) << ':' << sm.getSpellingColumnNumber(loc) << ": note: expanded from macro\n";
        }
    } else {
        os << "<no source>: " << level << ": " << msg << '\n';
    }
}

unique_ptr<ASTConsumer> LgsCLangFeAction::CreateASTConsumer(CompilerInstance& compilerInstance, StringRef file) {
    return make_unique<LgsCLangASTConsumer>(&compilerInstance.getASTContext(), lgsFile, errHandler);
}
