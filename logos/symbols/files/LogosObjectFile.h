#ifndef LOGOSOBJFILE_H
#define LOGOSOBJFILE_H
#include "LogosFile.h"
#include "funcs/LogosFunc.h"

class LogosObjectFile final : public LogosFile {
public:
    vector<LogosVarDec*> fields;
    vector<LogosFunc*> funcs;

    explicit LogosObjectFile(const string& name) : LogosFile(name) {}
    ~LogosObjectFile() override {
        for (const auto var : fields) {
            delete var;
        }
        for (const auto func : funcs) {
            delete func;
        }
    }
};

#endif //LOGOSOBJFILE_H
