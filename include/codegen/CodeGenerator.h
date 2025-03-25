#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Logos.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

class LgsFile;
class LgsValue;

class CodeGenerator {
public:
    static void generateModule(const path& buildDir, const LgsMainFile* mainFile, bool writeToFile = true);
    static void generateModule(const path& buildDir, LgsObject* obj, bool writeToFile = true);
    static Module* createModule(const string& objName);
    static void writeIRToFile(const Module* module, const path& buildDir, const path& name);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
