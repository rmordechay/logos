#include <iostream>
#include <fstream>
#include "antlr4-runtime/antlr4-runtime.h"
#include "LogosLexer.h"
#include "LogosParser.h"

using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open("../test.lgs");
    if (!stream) {
        std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    ANTLRInputStream input(stream);

    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);

    tree::ParseTree* tree = parser.entry();

    std::cout << "Parse Tree: " << tree->toStringTree(&parser) << std::endl;

    for (auto child : tree->children) {
        if (child->getText().starts_with("print")) {
            std::string text = child->getText();
            size_t start = text.find('"') + 1;
            size_t end = text.rfind('"');
            std::cout << text.substr(start, end - start) << std::endl;
        }
    }

    return 0;
}
