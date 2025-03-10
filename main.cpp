#include "cli/LogosCli.h"

int main(const int argc, char* argv[]) {
    auto parser = LogosCli(argc, argv);
    parser.execute();
    return 0;
}
