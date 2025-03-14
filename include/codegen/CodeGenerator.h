#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Logos.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

class LgsFile;
class LgsValue;

const auto targetTriple = sys::getDefaultTargetTriple();
inline TargetMachine* targetMachine = nullptr;

class CodeGenerator {
public:
    path buildDir;

    explicit CodeGenerator(const path& buildDir) : buildDir(buildDir) {}
    void init();
    void generateCode(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols);
    void generateModule(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols) const;
    static void generateModule(LgsObject* obj, const map<string, LgsSymbol>& globalSymbols, const path& buildDir);
    static Module* createModule(const string& objName);
    static void writeIRToFile(const Module* module, const path& buildDir, const path& name);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
