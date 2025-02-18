#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "symbols/LogosSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;

struct LogosStackFrame {
    Function* IRFunc = nullptr;
    map<string, LogosSymbol> symbols;

    LogosStackFrame() = default;
    explicit LogosStackFrame(Function* IRFunc) : IRFunc(IRFunc) {}
};

class LogosStack : public stack<LogosStackFrame> {
public:
    map<string, Module*> modules;

    void enterScope(Function* func);
    void enterScope();
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    void addLocalSymbol(const string& name, const LogosSymbol& symbol);
    void addGlobalSymbol(const string& name, const LogosSymbol& symbol);
    void setCurrentFunc(Function* value);
    void resetStack();
    ~LogosStack() = default;
private:
    map<string, LogosSymbol> globalSymbols;
};



#endif //LOGOSSTACK_H
