#include "extern/LgsCLang.h"
#include "data/LgsErrors.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLangVisitor.h"
#include "files/LgsFile.h"
#include "logos/LgsErrHandler.h"
#include "logos/Platform.h"
#include "utils/LgsUtils.h"

using namespace clang;

void LgsCLang::parse(LgsFile& lgsFile, LgsErrHandler& errHandler) const {
    for (const auto filePath : lgsFile.externFiles) {
        auto path = filePath->value;
        string code;
        auto cLibPath = clibRoot / "usr/include" / path;
        if (exists(cLibPath)) {
            code = getFileText(cLibPath);
        } else {
            assert(0);
        }
        if (code.empty()) {
            errHandler.handleError(E10047, &filePath->location, {path});
            continue;
        }
        runToolOnCodeWithArgs(std::make_unique<LgsCLangFeAction>(lgsFile, errHandler), code, {"-isysroot", clibRoot});
    }
}

void LgsCLang::compile(const vector<LgsStrConst*>& files) {
    if (files.empty()) return;
    for (const auto& file : files) {
        compileArgs.push_back(file->value);
    }
    compileArgs.push_back("-o");
    compileArgs.push_back(outputFilePath.string());

    vector<const char*> args;
    for (const auto& argStr : compileArgs) {
        args.push_back(argStr.c_str());
    }

    const auto targetTriple = sys::getDefaultTargetTriple();
    DiagnosticsEngine diags(new DiagnosticIDs(), new DiagnosticOptions(), new DiagnosticConsumer());
    Driver driver(args[0], targetTriple, diags, CLANG_BINARY, fs);
    driver.setCheckInputsExist(false);

    unique_ptr<Compilation> compilation(driver.BuildCompilation(args));
    const auto& jobs = compilation->getJobs();
    if (jobs.empty()) {
        return;
    }

    const auto& ccArgs = jobs.begin()->getArguments();
    auto invocation = make_unique<CompilerInvocation>();
    CompilerInvocation::CreateFromArgs(*invocation, ccArgs, diags);
    auto compilerInstance = make_unique<CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
    compilerInstance->createFileManager(fs);
    compilerInstance->createSourceManager(compilerInstance->getFileManager());

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
    default: assert(0);
    }
}

void LgsCLang::getClibRoot() const {
    DiagnosticsEngine diags(new DiagnosticIDs(), new DiagnosticOptions(), new DiagnosticConsumer());
    Driver driver(CLANG_BINARY, sys::getDefaultTargetTriple(), diags);
    const char* args[] = {CLANG_BINARY, "-x", "c", "-E"};
    const auto compilation = driver.BuildCompilation(ArrayRef(args));
    const auto& toolChain = compilation->getDefaultToolChain();
}