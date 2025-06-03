#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include <LgsValue.h>

class LgsForLoop;
class LgsVarDec;
class LgsSelection;
class LgsFuncCall;
class LgsReturn;
class LgsPatternMatch;
class LgsIfStmt;
class LgsContinueStmt;
class LgsBreakStmt;
class LgsAssignment;

class LgsStmt : virtual public LgsValue {
public:
    LgsVarDec* asVarDec();
    LgsIfStmt* asIfStmt();
    LgsAssignment* asAssignment();
    LgsForLoop* asLoop();
    LgsPatternMatch* asPatternMatch();
    LgsReturn* asReturn();
    LgsContinueStmt* asContinue();
    LgsBreakStmt* asBreakStmt();
    LgsFuncCall* asFuncCall();
    LgsSelection* asSelection();
    virtual void createIRStmt(Module* module, LgsRuntime* runtime) = 0;
    ~LgsStmt() override = default;
};

#endif //LOGOSSTMT_H
