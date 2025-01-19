#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LogosStackFrame.h"

#include <stack>

using namespace std;

class LogosStack : public stack<LogosStackFrame> {
public:
    void enterScope();
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    Function* getFunc(const string& name);
    void addSymbol(const string& name, LogosSymbol* symbol);
    void addFunc(const string& name, Function* value);
    void setCurrentFunc(Function* value);
    ~LogosStack() = default;
};



#endif //LOGOSSTACK_H
