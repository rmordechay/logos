#pragma once
#include "data/LgsTokens.h"
#include "data/LgsErrors.h"

struct LgsToken {
    LgsTokenType type = T_UNKNOWN;
    std::string lexeme = "";
    LgsLocation location;

    LgsToken() = default;
    LgsToken(const LgsTokenType type, const std::string& lexeme, const LgsLocation& location)
        : type(type),
          lexeme(lexeme),
          location(location) {
    }
};
