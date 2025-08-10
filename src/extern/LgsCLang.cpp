#include "extern/LgsCLang.h"
#include "configs/PlatformData.h"
#include "configs/LgsErrors.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLangVisitor.h"
#include "utils/LgsErrHandler.h"
#include "logos/LgsPaths.h"
#include "utils/LgsUtils.h"

void LgsCLang::parseFile(const string& filePath) {
    auto headerPath = filesystem::path(CLIB_INCLUDE) / filePath;
    if (isCLibHeader(headerPath)) {
        const auto code = getFileText(headerPath);
        clang::tooling::runToolOnCodeWithArgs(make_unique<LgsCLangFeAction>(headerPath), code, {"-isysroot", CLIB_ROOT});
    }
}

void LgsCLang::compile(const vector<LgsStrConst*>& files) const {
    const auto targetTriple = sys::getDefaultTargetTriple();
    clang::DiagnosticsEngine diags(new clang::DiagnosticIDs(), new clang::DiagnosticOptions(), new clang::DiagnosticConsumer());
    clang::driver::Driver driver("clang", targetTriple, diags);

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
    vector<string> compileArgs{"clang", "-c", "-isysroot", CLIB_ROOT};
    for (const auto& file : files) {
        compileArgs.push_back(file->value);
    }
    compileArgs.push_back("-o");
    compileArgs.push_back((paths.buildDir / "external_c.o").string());
    for (const auto& argStr : compileArgs) {
        args.push_back(argStr.c_str());
    }
}

string LgsCLang::getCode(LgsStrConst* filePath) {
    string code;
    const auto pathStr = filePath->value;
    const auto cLibPath = filesystem::path(CLIB_INCLUDE) / pathStr;
    if (filesystem::exists(cLibPath)) {
        return getFileText(cLibPath);
    }
    errHandler.addError(E10047, &filePath->location, {pathStr});
    return "";
}

void LgsCLang::setCHeaderPaths() {
    for (const auto& entry : filesystem::directory_iterator(CLIB_INCLUDE)) {
        if (!entry.is_regular_file()) continue;
        auto ext = entry.path().extension();
        if (ext == ".h" || ext == ".hpp" || ext == ".hh" || ext == ".hxx") {
            headers.push_back(entry.path().string());
        }
    }
    // TODO enable again more cross platform
    // for (const auto& entry : filesystem::directory_iterator(filesystem::path(CLIB_INCLUDE) / "sys/_types")) {
    //     if (!entry.is_regular_file()) continue;
    //     parseFile(entry.path().string());
    // }
}

bool LgsCLang::isCLibHeader(const filesystem::path& cLibPath) {
    return std::find(headers.begin(), headers.end(), cLibPath) != headers.end();
}