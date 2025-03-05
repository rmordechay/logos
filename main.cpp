#include "CommandLine.h"

int main(const int argc, char* argv[]) {
    auto parser = CommandLine();
    parser.parse(argc, argv);
    parser.execute();
    return 0;
}
