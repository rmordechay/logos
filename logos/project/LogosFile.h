#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <string>

class LogosFile {
public:
    explicit LogosFile(const std::string &code, const std::string &name);
    std::string code;
    std::string name;
};

#endif //LOGOSFILE_H
