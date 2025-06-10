#pragma once

#include "logos/LgsProject.h"

class LgsLinker {
public:
    bool link(LogosProject& project) const;
    bool generateObjFile(Module* module, const string& path) const;
    ~LgsLinker() = default;
};


