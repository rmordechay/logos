#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H


#include "LogosParser.h"


class SemAnalyser final {
    public:
    void checkLogosFile(LogosParser::LogosFileContext* ctx);
    void checkObjectFile(LogosParser::ObjectFileContext* ctx);
    void checkImportStatement(LogosParser::ImportStatementContext* ctx);
    void checkObjectImplements(LogosParser::ObjectImplementsContext* ctx);
};


#endif //SEMANTICANALYSER_H
