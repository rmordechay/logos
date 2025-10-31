#pragma once

const auto MAIN_FILE_TEMPLATE = R"(
    main() {
        print("Hello world")
    }
)";

const auto APP_CONFIG_FILE_TEMPLATE = R"(
    name = "%s"
    version = "1.0.0"
    activeEnv = "Production"

    required envs {

    }

    packages {

    }
)";
