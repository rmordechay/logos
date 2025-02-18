#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "symbols/LogosSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;

struct LogosStackFrame {
    map<string, LogosSymbol> symbols;
};

class LogosStack : public stack<LogosStackFrame> {
public:
    Function* currentFunc = nullptr;
    map<string, Module*> modules;

    void enterScope(Function* func);
    void enterScope();
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    void addLocalSymbol(const string& name, const LogosSymbol& symbol);
    void addGlobalSymbol(const string& name, const LogosSymbol& symbol);
    void reset();
    ~LogosStack() = default;
private:
    map<string, LogosSymbol> globalSymbols;
};



#endif //LOGOSSTACK_H
