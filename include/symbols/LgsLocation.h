#pragma once

struct LgsLocation {
    size_t lineNumberStart{};
    size_t lineNumberEnd{};
    size_t posInLineStart{};
    size_t posInLineEnd{};
    path filePath;

    string lineNumberStr() const {
        return to_string(lineNumberStart);
    }

    string getFullPath() const {
        return filePath.string() + ":" + lineNumberStr() + ":" + to_string(posInLineStart);
    }
};