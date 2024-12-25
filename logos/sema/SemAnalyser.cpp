#include "SemAnalyser.h"
#include "llvm/IR/LLVMContext.h"

void SemAnalyser::checkLogosFile(LogosParser::LogosFileContext* logosFile) {
    const auto objectFile = logosFile->objectFile();
    checkObjectFile(objectFile);
    checkObjectFile(objectFile);
}

void SemAnalyser::checkObjectFile(const LogosParser::ObjectFileContext* objectFile) {
    if (objectFile == nullptr) return;
}





