#ifndef LOGOSLOOPVAR_H
#define LOGOSLOOPVAR_H
#include <LgsValue.h>

class LgsType;

class LgsLoopVar final: public LgsValue {
public:
    string name;
    LgsType* type = nullptr;
    LgsArrayIndex* element = nullptr;

    explicit LgsLoopVar(const string& name) : name(name) {}
    explicit LgsLoopVar(const string& name, LgsType* type) : name(name), type(type) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsLoopVar() override;
};



#endif //LOGOSLOOPVAR_H
