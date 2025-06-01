#ifndef LGSLOCATION_H
#define LGSLOCATION_H
#include <filesystem>
#include <string>

struct Location {
    size_t lineNumber{};
    size_t posInLine{};

    std::string lineNumberStr() const {
        return std::to_string(lineNumber);
    }

    std::string getFullPath(const std::filesystem::path& path) const {
        return path.string() + ":" + lineNumberStr() + ":" + std::to_string(posInLine);
    }
};

#endif //LGSLOCATION_H
