#pragma once

struct LgsLocation {
    size_t lineStart = 0;
    size_t lineEnd = 0;
    size_t posStart = 0;
    size_t posEnd = 0;
    const char* filePath = "";
};
