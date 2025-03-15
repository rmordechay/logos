#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Logos.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

class LgsFile;
class LgsValue;

using LogosGlobals = const std::map<std::string, LgsSymbol>&;

class CodeGenerator {
public:
    static void generateCode(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols);
    static void generateModule(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols);
    static void generateModule(LgsObject* obj, const map<string, LgsSymbol>& globalSymbols);
    static Module* createModule(const string& objName);
    static void writeIRToFile(const Module* module, const path& name);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
