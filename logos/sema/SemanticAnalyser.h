#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H
#include "LogosBaseListener.h"


class SemanticAnalyser final : public LogosBaseListener {

    void enterLogosFile(LogosParser::LogosFileContext* ctx) override {
        std::cout << "SemanticAnalyser::enterLogosFile" << std::endl;
    }
};



#endif //SEMANTICANALYSER_H
