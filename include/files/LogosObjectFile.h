#ifndef LOGOSOBJFILE_H
#define LOGOSOBJFILE_H
#include "LogosFile.h"
#include "object/LogosObject.h"

class LogosObjectFile final : public LogosFile {
public:
    LogosObject *obj = nullptr;

    explicit LogosObjectFile(const string& name, const string& path) : LogosFile(name, path) {}
    ~LogosObjectFile() override;
};

inline LogosObjectFile::~LogosObjectFile() {
    delete obj;
}

#endif //LOGOSOBJFILE_H
