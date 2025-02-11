#include "application/LogosUtils.h"

using namespace std;

bool Utils::isLogosFile(const filesystem::directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

bool Utils::isMainFile(const filesystem::directory_entry& filePath) {
    return filePath.path().stem().string() == LOGOS_MAIN_FILE;
}

Module* Utils::createLLVMModuleFromFile(const string& filePath, LLVMContext& context, const TargetMachine& tm) {
    SMDiagnostic err;
    auto module = parseIRFile(filePath, err, context);
    module->setDataLayout(tm.createDataLayout());
    return module.release();
}

void Utils::emitLLVMFile(const string& filePath, const Module* const module) {
    error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
}

string Utils::getUnaryExprName(LogosUnaryExpr* expr) {
    if (const auto func = dynamic_cast<LogosFunc*>(expr)) {
        return func->name;
    }
    if (const auto func = dynamic_cast<LogosVariable*>(expr)) {
        return func->name;
    }
    if (const auto constructor = dynamic_cast<LogosConstructor*>(expr)) {
        return constructor->name;
    }
    return nullptr;
}
