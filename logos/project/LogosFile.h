#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <string>

class LogosFile {
public:
    explicit LogosFile(const std::string &code);
    std::string code;
};

#endif //LOGOSFILE_H
