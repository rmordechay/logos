#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H


#include "LogosParser.h"


class SemAnalyser final {
    public:
    void checkLogosFile(LogosParser::LogosFileContext* logosFile);
    void checkObjectFile(const LogosParser::ObjectFileContext* objectFile);
};



#endif //SEMANTICANALYSER_H
