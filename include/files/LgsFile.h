#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <string>
#include <assert.h>
#include <json/json.hpp>
#include <llvm/IR/Module.h>


class LgsRuntime;
using namespace std;
using namespace nlohmann;

class LgsFile {
public:
    string name;
    string code;
    string absPath;
    string relPath;
    vector<string> externFiles;

    explicit LgsFile(const string& name, const string& path) : name(name), absPath(path) {}
    virtual void generateIR();
    virtual void format();
    virtual json asJSON();
    virtual ~LgsFile() = default;
};

inline void LgsFile::generateIR() {}

inline void LgsFile::format() {
    assert(false);
}

inline json LgsFile::asJSON() {
    assert(false);
}

#endif //LOGOSFILE_H
