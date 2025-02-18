#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Application.h>

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
    LogosStack& logosStack;
    map<string, LogosFile*>& files;

    CodeGenerator(LogosStack& logosStack, map<string, LogosFile*>& files) : logosStack(logosStack), files(files) {
        initIR();
    }

    void generateCode() const;
    void generateMainModule() const;
    static void generateObjModule(LogosObject* obj, CodeGenMetadata& metadata);
    static void writeIRToFile(const Module* module, const string& name);
    static CodeGenMetadata createMetadata(IRBuilder<>& builder, LogosStack* logosStack, Module* module);
    static void initIR();
    static void emitIRFile(const string& filePath, const Module* module);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
