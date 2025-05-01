#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include <LgsValue.h>

class LgsSelection;
class LgsFuncCall;
class LgsReturn;
class LgsPatternMatch;
class LgsIfStmt;
class LgsContinue;
class LgsBreakStmt;
class LgsAssignment;

class LgsStmt : virtual public LgsValue {
public:
    LgsVarDec* asVarDec();
    LgsIfStmt* asIfStmt();
    LgsAssignment* asAssignment();
    LgsLoop* asLoop();
    LgsPatternMatch* asPatternMatch();
    LgsReturn* asReturn();
    LgsContinue* asContinue();
    LgsBreakStmt* asBreakStmt();
    LgsFuncCall* asFuncCall();
    LgsSelection* asSelection();
    virtual void createIRStmt(CodeGenMetadata* metadata) = 0;
    ~LgsStmt() override = default;
};

#endif //LOGOSSTMT_H
