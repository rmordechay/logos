#pragma once

const auto MAIN_FILE_TEMPLATE = R"(
    main() {
        print("%s...")
    }
)";

const auto APP_CONFIG_FILE_TEMPLATE = R"(
    name = "%s"
    version = "1.0.0"
    activeEnv = "Production"

    required envs {
        // exampleConfig: Int
    }

    packages {
        // "github/user/repo" "1.0.1" alias
    }
)";
