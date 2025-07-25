#include "LgsValue.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsValue::setLocation(const Token* start, const Token* end, const path& filePath) {
    location.lineNumberStart = start->getLine();
    location.posInLineStart = start->getCharPositionInLine() + 1;
    if (!end) {
        location.lineNumberEnd = start->getLine();
        location.posInLineEnd = start->getCharPositionInLine() + start->getText().length();
    }
    location.filePath = filePath;
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

string LgsValue::format(string& indentStr) {
    assert(0);
}
