#include "extern/LgsCLang.h"
#include "data/LgsErrors.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLangVisitor.h"
#include "logos/LgsErrHandler.h"
#include "logos/Platform.h"
#include "utils/LgsUtils.h"

using namespace clang;

void LgsCLang::parseFile(const LgsStrConst* filePaths) {
    const auto pathStr = filePaths->value;
    auto headerPath = paths.clibInclude / pathStr;
    if (isCLibHeader(headerPath)) {
        const auto code = getFileText(headerPath);
        runToolOnCodeWithArgs(make_unique<LgsCLangFeAction>(headerPath), code, {"-isysroot", paths.clibRoot});
    } else {
        return errHandler.handleError(E10047, &filePaths->location, {pathStr});
    }
}

void LgsCLang::compile(const vector<LgsStrConst*>& files) const {
    const auto targetTriple = sys::getDefaultTargetTriple();
    DiagnosticsEngine diags(new DiagnosticIDs(), new DiagnosticOptions(), new DiagnosticConsumer());
    Driver driver(CLANG_BINARY, targetTriple, diags);

    auto invocation = make_unique<CompilerInvocation>();
    CompilerInvocation::CreateFromArgs(*invocation, getCompileArgs(files), diags);
    auto compilerInstance = make_unique<CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
    compilerInstance->createFileManager();
    compilerInstance->createSourceManager(compilerInstance->getFileManager());

    switch (compilerInstance->getFrontendOpts().ProgramAction) {
    case frontend::ActionKind::EmitObj: {
        EmitObjAction action;
        compilerInstance->ExecuteAction(action);
        break;
    }
    case frontend::ActionKind::EmitAssembly: {
        EmitAssemblyAction action;
        compilerInstance->ExecuteAction(action);
        break;
    }
    default: break;
    }
}

vector<const char*> LgsCLang::getCompileArgs(const vector<LgsStrConst*>& files) const {
    vector<const char*> args;
    vector<string> compileArgs{CLANG_BINARY, "-c", "-isysroot", paths.clibRoot};
    for (const auto& file : files) {
        compileArgs.push_back(file->value);
    }
    compileArgs.push_back("-o");
    compileArgs.push_back((paths.buildDir / "external_c.o").string());
    for (const auto& argStr : compileArgs) {
        args.push_back(argStr.c_str());
    }
    return args;
}

string LgsCLang::getCode(const LgsStrConst* filePath) {
    string code;
    const auto pathStr = filePath->value;
    const auto cLibPath = paths.clibInclude / pathStr;
    if (exists(cLibPath)) {
        return getFileText(cLibPath);
    }
    errHandler.handleError(E10047, &filePath->location, {pathStr});
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
}

void LgsCLang::getClibRoot() const {
    DiagnosticsEngine diags(new DiagnosticIDs(), new DiagnosticOptions(), new DiagnosticConsumer());
    auto invocation = make_unique<CompilerInvocation>();
    CompilerInvocation::CreateFromArgs(*invocation, {CLANG_BINARY, "-x", "c", "-E", "-"}, diags);
    auto compilerInstance = make_unique<CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
}

bool LgsCLang::isCLibHeader(const path& cLibPath) {
    return std::find(headers.begin(), headers.end(), cLibPath) != headers.end();
}