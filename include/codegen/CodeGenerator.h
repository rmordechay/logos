#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Application.h>
#include <llvm/Target/TargetMachine.h>

class LogosFile;
class LogosValue;

const auto targetTriple = sys::getDefaultTargetTriple();
inline TargetMachine* targetMachine = nullptr;

class CodeGenerator {
public:
    map<string, LogosSymbol> globalSymbols;
    const LogosMainFile* mainFile;

    explicit CodeGenerator(const LogosMainFile* mainFile) : mainFile(mainFile) {
        initIR();
    }

    void generateCode(const map<string, LogosSymbol>& globalSymbols) const;
    void generateMainModule(const map<string, LogosSymbol>& globalSymbols) const;
    static Module* createModule(const string& objName);
    static void generateObjectModule(LogosObject* obj, const map<string, LogosSymbol>& globalSymbols);
    static void writeIRToFile(const Module* module, const string& name);
    static void initIR();
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
