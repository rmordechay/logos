#include "codegen/LgsLinker.h"
#include "utils/LgsUtils.h"

bool LgsLinker::generateObjFile(Module* module, const string& path) const {
    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(path, ec, sys::fs::OF_None);
    const auto addedPassFailed = getTargetMachine()->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        cerr << ec.message() << endl;
        return false;
    }

    if (verifyModule(*module, &errs())) {
        errs().flush();
        return false;
    }

    pass.run(*module);
    outputStream.flush();
    outputStream.close();
    return true;
}
