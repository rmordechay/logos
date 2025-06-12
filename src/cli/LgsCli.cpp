#include "cli/LgsCli.h"

#include "cli/LgsFormatCmd.h"
#include "cli/LgsGenerateCmd.h"
#include "cli/LgsRunCmd.h"
#include "data/LgsDefinitions.h"


#include <sstream>

void LgsCli::execute() const {
    if (argc < 2) {
        lgsLog("Error: not enough arguments.\n\n");
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
    txt << "Logos version: " + string(LOGOS_VERSION) << endl;
    txt << "Architecture: " + string(ARCH_NAME) << endl;
    txt << "Operation System: " + string("macOS") << endl;
    lgsLog(txt.str());
}

void LgsCli::printHelp() {
    ostringstream txt;
    txt << "Usage: lgs <command> <options>" << "\n\n";

    txt << "Commands:" << endl;
    txt << "run                       execute a logos script or run application" << endl;
    txt << "help                      print logos help" << endl;
    txt << "version, -v, --version    print logos version" << endl;

    txt << endl << "For more information: lgs [command] help" << endl;
    lgsLog(txt.str());
}

void LgsCli::exitWithMsg(const string& errorMsg) {
    lgsLog(errorMsg + "\n\n");
    exit(0);
}
