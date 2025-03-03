#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Application.h>

#include <llvm/IR/Module.h>
#include <clang/Frontend/CompilerInstance.h>

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
    static void generateObjModule(LogosObject* obj, const map<string, LogosSymbol>& globalSymbols);
    static void writeIRToFile(const Module* module, const string& name);
    static void initIR();
    static void emitIRFile(const string& filePath, const Module* module);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
