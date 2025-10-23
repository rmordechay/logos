#include "lgsc/LgsCLang.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsFile.h"
#include "lgsc/LgsCLangVisitor.h"
#include "logos/LgsPaths.h"
#include "utils/LgsUtils.h"
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Tooling/Tooling.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/CompilerInstance.h>
#include <llvm/TargetParser/Host.h>

void LgsCLang::resolveCPaths(LgsFile* lgsFile) {
    for (const auto externalCPath : lgsFile->externalCPaths) {
        const auto entryPath = resolveExternalFile(externalCPath);
        if (entryPath == "") continue;
        parseFile(entryPath, lgsFile);
    }
}

void LgsCLang::parseFile(const fs::path& fileName, LgsFile* lgsFile) const {
    if (fileName == "") return;
    const auto filePath = paths.cLibHeadersDir / fileName;
    const auto code = getFileText(filePath);
    clang::tooling::runToolOnCodeWithArgs(std::make_unique<LgsCLangFeAction>(lgsFile), code, {"-isysroot", paths.cLibRoot.c_str()});
}

void LgsCLang::compile(const std::vector<LgsStrConst*>& files) const {
    const auto targetTriple = llvm::sys::getDefaultTargetTriple();
    clang::DiagnosticsEngine diags(new clang::DiagnosticIDs(), new clang::DiagnosticOptions(), new clang::DiagnosticConsumer());
    clang::driver::Driver driver("clang", targetTriple, diags);
    auto invocation = std::make_unique<clang::CompilerInvocation>();
    const auto args = getCompileArgs(files);
    clang::CompilerInvocation::CreateFromArgs(*invocation, args, diags);
    auto compilerInstance = std::make_unique<clang::CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
    compilerInstance->createFileManager();
    compilerInstance->createSourceManager(compilerInstance->getFileManager());

    switch (compilerInstance->getFrontendOpts().ProgramAction) {
    case clang::frontend::ActionKind::EmitObj: {
        clang::EmitObjAction action;
        compilerInstance->ExecuteAction(action);
        break;
    }
    case clang::frontend::ActionKind::EmitAssembly: {
        clang::EmitAssemblyAction action;
        compilerInstance->ExecuteAction(action);
        break;
    }
    default: break;
    }
}

std::vector<const char*> LgsCLang::getCompileArgs(const std::vector<LgsStrConst*>& files) const {
    std::vector compileArgs{"clang", "-c", "-isysroot", paths.cLibRoot.c_str()};
    for (const auto& file : files) {
        compileArgs.push_back(file->value.c_str());
    }
    compileArgs.push_back("-o");
    compileArgs.push_back((paths.buildDir / "external_c.o").c_str());
    return compileArgs;
}

fs::path LgsCLang::resolveExternalFile(LgsStrConst* filePath) {
    if (fs::exists(filePath->value)) return filePath->value;
    const auto cLibHeaderFile = paths.cLibHeadersDir / filePath->value;
    if (fs::exists(cLibHeaderFile)) return cLibHeaderFile;
    errHandler.addError(E10047, &filePath->location, {filePath->value});
    return "";
}
