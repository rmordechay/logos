#include "application/CommandLine.h"

void CommandLine::parse(const int argc, char* argv[]) {
    if (argc < 2) {
        helpCommand();
        exit(0);
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

void CommandLine::printVersion() const {
    std::cout << "Logos version: " + string(LOGOS_VERSION) << std::endl;
    std::cout << "Architecture: " + string(ARCH_NAME) << std::endl;
    std::cout << "Operation System: " + string(OS_NAME) << std::endl;
}

void CommandLine::execute() const {
    if (command == "run") {
        runCommand();
    } else if (command == "build") {
        buildCommand();
    } else if (command == "help") {
        buildCommand();
    } else if (command == "version") {
        printVersion();
    } else {
        helpCommand();
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
    Application project("../project/src");
    project.runLogos();
}

void CommandLine::buildCommand() const {

}

void CommandLine::helpCommand() {
    std::cout << "Usage: lgs command [options]" << "\n\n";
    std::cout << "Commands:" << '\n';
    std::cout << "run                       execute a logos script" << '\n';
    std::cout << "help                      print logos help" << '\n';
    std::cout << "version, -v, --version    print logos version" << '\n';
}
