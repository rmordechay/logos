#pragma once

class LgsLinker {
public:
    bool generateObjFile(Module* module, const string& path) const;
    ~LgsLinker() = default;
};


