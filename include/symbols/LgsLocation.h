#pragma once

struct Location {
    size_t lineNumber{};
    size_t posInLine{};

    string lineNumberStr() const {
        return to_string(lineNumber);
    }

    string getFullPath(const path& path) const {
        return path.string() + ":" + lineNumberStr() + ":" + to_string(posInLine);
    }
};
