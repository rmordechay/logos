#ifndef LOGOSMETHODCALL_H
#define LOGOSMETHODCALL_H
#include "LgsFuncCall.h"
#include "LogosUnaryExpr.h"
#include "funcs/LgsMethodImpl.h"

class LgsMethodCall final : public LgsFuncCall {
public:
    LgsMethodImpl* methodImpl = nullptr;

    explicit LgsMethodCall(const string& name, const vector<LgsExpr*>& args = {}) : LgsFuncCall(name, args) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsMethodCall() override;
};

#endif //LOGOSMETHODCALL_H
