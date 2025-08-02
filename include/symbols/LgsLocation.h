#pragma once

struct LgsLocation {
    size_t lineStart = 0;
    size_t lineEnd = 0;
    size_t posStart = 0;
    size_t posEnd = 0;
    path filePath = "";

    string lineNumberStr() const {
        return to_string(lineStart);
    }

    string getFullPath() const {
        return filePath.string() + ":" + lineNumberStr() + ":" + to_string(posStart);
    }
};
