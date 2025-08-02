#include "extern/LgsCLang.h"
#include "configs/LgsErrors.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLangVisitor.h"
#include "../../include/utils/LgsErrHandler.h"
#include "logos/LgsPaths.h"
#include "utils/LgsUtils.h"

using namespace clang;

#define CLANG_BINARY "clang"

void LgsCLang::parseFile(const string& filePath) {
    auto headerPath = paths.clibInclude / filePath;
    if (isCLibHeader(headerPath)) {
        const auto code = getFileText(headerPath);
        runToolOnCodeWithArgs(make_unique<LgsCLangFeAction>(headerPath), code, {"-isysroot", paths.clibRoot});
    }
}

void LgsCLang::compile(const vector<LgsStrConst*>& files) const {
    const auto targetTriple = sys::getDefaultTargetTriple();
    DiagnosticsEngine diags(new DiagnosticIDs(), new DiagnosticOptions(), new DiagnosticConsumer());
    Driver driver(CLANG_BINARY, targetTriple, diags);

    auto invocation = make_unique<CompilerInvocation>();
    vector<const char*> args;
    setCompileArgs(files, args);
    CompilerInvocation::CreateFromArgs(*invocation, args, diags);
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
    DiagnosticsEngine diags(new DiagnosticIDs(), new DiagnosticOptions(), new DiagnosticConsumer());
    auto invocation = make_unique<CompilerInvocation>();
    CompilerInvocation::CreateFromArgs(*invocation, {CLANG_BINARY, "-x", "c", "-E", "-"}, diags);
    auto compilerInstance = make_unique<CompilerInstance>();
    compilerInstance->setInvocation(std::move(invocation));
}

bool LgsCLang::isCLibHeader(const path& cLibPath) {
    return std::find(headers.begin(), headers.end(), cLibPath) != headers.end();
}