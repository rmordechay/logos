#include "application/CommandLine.h"

void CommandLine::parse(const int argc, char* argv[]) {
    if (argc < 2) {
        assert(false && "No command provided");
    }
    rootPath = current_path();
    command = argv[1];
    for (int i = 2; i < argc; ++i) {
        string arg = argv[i];
        if (arg.substr(0, 2) == "--") {
            parseLongFlag(arg);
        } else if (arg[0] == '-') {
            flags.emplace_back(arg.substr(1));
        } else {
            commands.push_back(arg);
        }
    }
}

void CommandLine::execute() const {
    if (command == "run") {
        runCommand();
    } else if (command == "build") {
        buildCommand();
    } else if (command == "help") {
        helpCommand();
    } else {
        throw runtime_error("Unknown command: " + command);
    }
}

void CommandLine::parseLongFlag(const string& arg) {
    const auto equalPos = arg.find('=');
    if (equalPos != string::npos) {
        const auto flagName = arg.substr(2, equalPos - 2);
        const auto flagValue = arg.substr(equalPos + 1);
        kvFlags[flagName] = flagValue;
    } else {
        flags.emplace_back(arg.substr(2));
    }
}

void CommandLine::runCommand() const {
    Application project("/Users/r.mordechay/Desktop/Programming/logos/project/src");
    project.runLogos();
}

void CommandLine::buildCommand() const {

}

void CommandLine::helpCommand() {

}
