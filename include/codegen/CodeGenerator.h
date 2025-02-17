#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "LogosStack.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"

#include <llvm/IR/Module.h>
#include "llvm/Passes/PassBuilder.h"
#include <clang/Frontend/CompilerInstance.h>

class LogosFile;
class LogosValue;

class CodeGenerator {
public:
    vector<Module*> modules;
    vector<LogosValue*> codeNodes;

    CodeGenerator() { initIR(); }
    static void generate(const map<string, LogosFile*>& files, LogosStack& theStack);
    static void initIR();
    static void generateMainModule(const LogosMainFile* mainFile, CodeGenMetadata metadata);
    static void generateObjModule(LogosObject* obj, LogosStack* theStack);
    static void emitIRFile(const string& filePath, const Module* module);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
