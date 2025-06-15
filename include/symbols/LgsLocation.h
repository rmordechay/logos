#pragma once

struct Location {
    size_t lineNumber{};
    size_t posInLine{};
    path* filePath = nullptr;

    string lineNumberStr() const {
        return to_string(lineNumber);
    }

    string getFullPath(const path& path) const {
        return path.string() + ":" + lineNumberStr() + ":" + to_string(posInLine);
    }
};

inline Location getLocation(const Token* ctx, path* filePath) {
    Location location;
    location.lineNumber = ctx->getLine();
    location.posInLine = ctx->getCharPositionInLine() + 1;
    location.filePath = filePath;
    return location;
}