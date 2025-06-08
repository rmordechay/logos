#pragma once

struct Location {
    size_t lineNumber{};
    size_t posInLine{};

    std::string lineNumberStr() const {
        return std::to_string(lineNumber);
    }

    std::string getFullPath(const path& path) const {
        return path.string() + ":" + lineNumberStr() + ":" + std::to_string(posInLine);
    }
};


