#pragma once

struct Location {
    size_t lineNumberStart{};
    size_t lineNumberEnd{};
    size_t posInLineStart{};
    size_t posInLineEnd{};
    path filePath;

    string lineNumberStr() const {
        return to_string(lineNumberStart);
    }

    string getFullPath(const path& path) const {
        return path.string() + ":" + lineNumberStr() + ":" + to_string(posInLineStart);
    }
};