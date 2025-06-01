#include "../../include/extern/LgsC.h"

#include "../../include/extern/LgsCInterface.h"
#include "codegen/CodegenMetadata.h"
#include "logos/LgsGlobals.h"
#include "logos/Platform.h"

#include <clang/Basic/Diagnostic.h>
#include <llvm/Support/raw_ostream.h>
#include "utils/LgsUtils.h"
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Frontend/FrontendOptions.h>
#include <clang/Tooling/Tooling.h>

#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace clang;

void LgsC::compile(const vector<string>& files) {
    if (files.empty()) return;
    vector<string> argStrings{
        "clang",
        "-c",
        "-isysroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
    };
    for (const auto& file : files) {
        argStrings.push_back(file);
    }
    argStrings.push_back("-o");
    argStrings.push_back((paths.buildDir / "c.o").string());

    vector<const char*> args;
    for (const auto& argStr : argStrings) {
        args.push_back(argStr.c_str());
    }

    auto diags = CompilerInstance::createDiagnostics(*fs, new DiagnosticOptions, &dc, false);
    clang::driver::Driver driver(args[0], targetTriple, *diags, "cc", fs);
    driver.setCheckInputsExist(false);

    unique_ptr<clang::driver::Compilation> compilation(driver.BuildCompilation(args));
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

void LgsC::parse(const vector<string>& files) const {
    for (const auto file : files) {
        const auto code = getFileText(file);
        tooling::runToolOnCodeWithArgs(std::make_unique<LgsCFrontendAction>(), code, {"-isysroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"});
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
