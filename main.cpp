#include "cli/LogosCli.h"

int main(const int argc, char* argv[]) {
    const LogosCli cli(argc, argv);
    cli.execute();
    return 0;
}
