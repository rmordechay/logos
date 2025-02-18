#include "SemaAnalyser.h"
#include "LogosErrors.h"
#include "SemaFileAnalyser.h"
#include "exprs/LogosBinaryExpr.h"

#include <ThreadPool.h>
#include <format>

bool SemaAnalyser::analyse() {
    collectGlobals();
    ThreadPool threadPool;
    for (auto& [name, file] : files) {
        threadPool.runTask([this, file] {
            auto semaFile = SemaFileAnalyser(mainStack);
            visitLogosFile(file, semaFile);
        });
    }
    threadPool.wait();
    mainStack.reset();
    return successful;
}

void SemaAnalyser::collectGlobals() {
    for (const auto& [name, file] : files) {
        if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
            const auto object = objFile->obj;
            mainStack.addGlobalSymbol(object->name(), LogosSymbol(OBJECT, object));
        }
    }
}

void SemaAnalyser::visitLogosFile(LogosFile* file, SemaFileAnalyser& semFile) {
    if (const auto mainFile = dynamic_cast<LogosMainFile*>(file)) {
        semFile.visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
        semFile.visitObjectFile(objFile);
    }
}



SemaAnalyser::~SemaAnalyser() {
    for (const auto& file : files) {
        delete file.second;
    }
}
