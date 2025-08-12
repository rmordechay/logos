#include "cli/LgsCli.h"
#include "cli/LgsFormatCmd.h"
#include "cli/LgsGenerateCmd.h"
#include "cli/LgsRunCmd.h"

void LgsCli::execute() const {
    if (argc < 2) {
        logInfo("Error: not enough arguments.\n\n");
        printHelp();
        exit(0);
    }

    const string cmd = argv[1];
    if (cmd == "run") {
        LgsRunCmd command(argc, argv);
        command.validate();
        command.runCmd();
    } else if (cmd == "format") {
        LgsFormatCmd command(argc, argv);
        command.validate();
        command.runCmd();
    } else if (cmd == "generate") {
        LgsGenerateCmd command(argc, argv);
        command.validate();
        command.runCmd();
    } else if (cmd == "version" || cmd == "-v" || cmd == "--version") {
        printVersion();
    }
}

void LgsCli::printVersion() {
    ostringstream txt;
    txt << "Logos version: " + string(LOGOS_VERSION) << '\n';
    logInfo(txt.str());
}

void LgsCli::printHelp() {
    ostringstream txt;
    txt << "Usage: lgs <command> <options>" << "\n\n";
    txt << "Commands:" << '\n';
    txt << "run                       execute a logos script or run application" << '\n';
    txt << "help                      print logos help" << '\n';
    txt << "version, -v, --version    print logos version" << '\n';
    txt << '\n' << "For more information: lgs [command] help" << '\n';
    logInfo(txt.str());
}

void LgsCli::exitWithMsg(const string& errorMsg) {
    logInfo(errorMsg + "\n\n");
    exit(0);
}
