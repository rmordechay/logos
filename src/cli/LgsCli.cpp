#include "cli/LgsCli.h"

#include "LgsGenerateCmd.h"
#include "LgsRunCmd.h"
#include <iostream>

void LgsCli::execute() const {
    if (argc < 2) {
        cout << "Error: not enough arguments." << "\n\n";
        printHelp();
        exit(0);
    }

    const string cmd = argv[1];
    if (cmd == "run") {
        LgsRunCmd command(argc, argv);
        command.runCmd();
    } else if (cmd == "generate") {
        LgsGenerateCmd command(argc, argv);
        command.runCmd();
    } else if (cmd == "version" || cmd == "-v" || cmd == "--version") {
        printVersion();
    }
}

void LgsCli::printVersion() {
    ostringstream txt;
    txt << "Logos version: " + string(LOGOS_VERSION) << endl;
    txt << "Architecture: " + string(ARCH_NAME) << endl;
    txt << "Operation System: " + string(OS_NAME) << endl;
    cout << txt.str();

}

void LgsCli::printHelp() {
    ostringstream txt;
    txt << "Usage: lgs command [options]" << "\n\n";

    txt << "Commands:" << '\n';
    txt << "run                       execute a logos script or run application" << '\n';
    txt << "help                      print logos help" << '\n';
    txt << "version, -v, --version    print logos version" << '\n';

    txt << '\n' << "For more information: lgs [command] help" << '\n';
    cout << txt.str();
}

void LgsCli::exitWithMsg(const string& errorMsg) {
    cout << errorMsg << "\n\n";
    exit(0);
}
