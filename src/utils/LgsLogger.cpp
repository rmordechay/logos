#include "utils/LgsLogger.h"

void lgsLog(const string& text, const LogLevel level) {
    if (level == ERROR) {
        cerr << text << std::endl;
    } else {
        cout << text << std::endl;
    }
}
