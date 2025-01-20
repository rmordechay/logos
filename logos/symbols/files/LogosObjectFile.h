#ifndef LOGOSOBJFILE_H
#define LOGOSOBJFILE_H
#include "LogosFile.h"
#include "object/LogosObject.h"

class LogosObjectFile final : public LogosFile {
public:
    LogosObject *obj = nullptr;
    explicit LogosObjectFile(const string& name) : LogosFile(name) {}
    ~LogosObjectFile() override = default;
};

#endif //LOGOSOBJFILE_H
