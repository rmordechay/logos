#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <string>
#include <assert.h>

class LgsStack;
using namespace std;
using namespace filesystem;

class LgsFile {
public:
    string name;
    string code;
    string absPath;
    string relPath;

    explicit LgsFile(const string& name, const string& path) : name(name), absPath(path) {}
    virtual void format();
    virtual json asJSON();
    virtual ~LgsFile() = default;
};

inline void LgsFile::format() {
    assert(false);
}

inline json LgsFile::asJSON() {
    assert(false);
}

#endif //LOGOSFILE_H
