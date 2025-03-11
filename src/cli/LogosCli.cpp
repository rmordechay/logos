#include "cli/LogosCli.h"

#include "LogosGenerateCmd.h"
#include "LogosRunCmd.h"
#include <iostream>

void LogosCli::execute() const {
    if (argc < 2) {
        cout << "Error: not enough arguments." << "\n\n";
        printHelp();
        exit(0);
    }

    const string cmd = argv[1];
    if (cmd == "run") {
        LogosRunCmd command;
        command.runCmd(argc, argv);
    } else if (cmd == "generate") {
        LogosGenerateCmd command;
        command.runCmd(argc, argv);
    } else if (cmd == "version" || cmd == "-v" || cmd == "--version") {
        printVersion();
    }
}

void LogosCli::printVersion() {
    ostringstream txt;
    txt << "Logos version: " + string(LOGOS_VERSION) << endl;
    txt << "Architecture: " + string(ARCH_NAME) << endl;
    txt << "Operation System: " + string(OS_NAME) << endl;
    cout << txt.str();

}

void LogosCli::printHelp() {
    ostringstream txt;
    txt << "Usage: lgs command [options]" << "\n\n";

    txt << "Commands:" << '\n';
    txt << "run                       execute a logos script or run application" << '\n';
    txt << "help                      print logos help" << '\n';
    txt << "version, -v, --version    print logos version" << '\n';

    txt << '\n' << "For more information: lgs [command] help" << '\n';
    cout << txt.str();
}

void LogosCli::exitWithMsg(const string& errorMsg) {
    cout << errorMsg << "\n\n";
    exit(0);
}
