#pragma once

class LgsCli {
public:
    int argc;
    char** argv;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    void execute() const;
};
