#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsType.h"
#include "stmts/LgsField.h"
#include <string>

class LgsStr final : public LgsType {
public:

    static constexpr auto name = "Str";

    const string getName() const override;
    size_t size() override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    static void cleanStr(string& value);
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};

inline void LgsStr::cleanStr(string& value) {
    value.erase(0, 1);
    value.pop_back();
}

/**
 * FNV-1a 32-bit hash
 */
inline uint32_t LgsStr::hashString(const string& str) {
    uint32_t hash = 2166136261u;
    for (const auto c : str) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

#endif // LOGOSSTRING_H
