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
    LogosStack& theStack;
    map<string, LogosFile*>& files;

    CodeGenerator(LogosStack& theStack, map<string, LogosFile*>& files) : theStack(theStack), files(files) {
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
