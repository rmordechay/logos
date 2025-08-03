#include "extern/LgsCLang.h"
#include "configs/LgsErrors.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLangVisitor.h"
#include "utils/LgsErrHandler.h"
#include "logos/LgsPaths.h"
#include "utils/LgsUtils.h"
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/CompilerInstance.h>

#define CLANG_BINARY "clang"

void LgsCLang::parseFile(const string& filePath) {
    auto headerPath = paths.clibInclude / filePath;
    if (isCLibHeader(headerPath)) {
        const auto code = getFileText(headerPath);
        clang::tooling::runToolOnCodeWithArgs(make_unique<LgsCLangFeAction>(headerPath), code, {"-isysroot", paths.clibRoot});
    }
}

void LgsCLang::compile(const vector<LgsStrConst*>& files) {
    const auto targetTriple = sys::getDefaultTargetTriple();
    clang::DiagnosticsEngine diags(new clang::DiagnosticIDs(), new clang::DiagnosticOptions(), new clang::DiagnosticConsumer());
    clang::driver::Driver driver(CLANG_BINARY, targetTriple, diags);

    auto invocation = make_unique<clang::CompilerInvocation>();
    vector<const char*> args;
    setCompileArgs(files, args);
    clang::CompilerInvocation::CreateFromArgs(*invocation, args, diags);
    auto compilerInstance = make_unique<clang::CompilerInstance>();
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

void LgsCLang::setCompileArgs(const vector<LgsStrConst*>& files, vector<const char*>& args) const {
    vector<string> compileArgs{CLANG_BINARY, "-c", "-isysroot", paths.clibRoot};
    for (const auto& file : files) {
        compileArgs.push_back(file->value);
    }
    compileArgs.push_back("-o");
    compileArgs.push_back((paths.buildDir / "external_c.o").string());
    for (const auto& argStr : compileArgs) {
        args.push_back(argStr.c_str());
    }
}

string LgsCLang::getCode(const LgsStrConst* filePath) {
    string code;
    const auto pathStr = filePath->value;
    const auto cLibPath = paths.clibInclude / pathStr;
    if (exists(cLibPath)) {
        return getFileText(cLibPath);
    }
    errHandler.addError(E10047, &filePath->location, {pathStr});
    return "";
}

void LgsCLang::setCHeaderPaths() {
    assert(paths.clibInclude != "");
    for (const auto& entry : directory_iterator(paths.clibInclude)) {
        if (!entry.is_regular_file()) continue;
        auto ext = entry.path().extension();
        if (ext == ".h" || ext == ".hpp" || ext == ".hh" || ext == ".hxx") {
            headers.push_back(entry.path().string());
        }
    }

    for (const auto& entry : directory_iterator(paths.clibInclude / "sys/_types")) {
        if (!entry.is_regular_file()) continue;
        parseFile(entry.path().string());
        time_t now = time(nullptr);
    }
}

void LgsCLang::getClibRoot() const {
    clang::DiagnosticsEngine diags(new clang::DiagnosticIDs(), new clang::DiagnosticOptions(), new clang::DiagnosticConsumer());
    auto invocation = make_unique<clang::CompilerInvocation>();
    clang::CompilerInvocation::CreateFromArgs(*invocation, {CLANG_BINARY, "-x", "c", "-E", "-"}, diags);
    auto compilerInstance = make_unique<clang::CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
}

bool LgsCLang::isCLibHeader(const path& cLibPath) {
    return std::find(headers.begin(), headers.end(), cLibPath) != headers.end();
}