#include "logos/LgsPkgManager.h"

#include <openssl/evp.h>
#include <__ostream/basic_ostream.h>
#include <assert.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <iomanip>
#include <system_error>

#include "files/LgsAppFile.h"
#include "logos/LgsApp.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "LgsVersion.h"
#include "errors/LgsErrHandler.h"
#include "logos/LgsAppConfigs.h"
#include "logos/LgsPaths.h"

namespace fs = std::filesystem;
#define MAX_DOWNLOAD_FILE_SIZE 10'000 * 1024

bool unzipFile(const std::string& zipPath, const std::string& destDir) {
    return runCmd("unzip " + zipPath + " -d " + destDir);
}

bool downloadFile(const std::string& url, const std::string& outPath) {
    assert(url.substr(0, 8) == "https://");
    const auto cmd = "curl -fsSL --max-filesize " + std::to_string(MAX_DOWNLOAD_FILE_SIZE) + " -o " + outPath + " " + url;
    return std::system(cmd.c_str()) == 0;
}

void LgsPkgManager::install() {
    paths.findLgsRootDir();
    assert(fs::exists(paths.lgsPackagesDir));
    LgsApp app;
    app.configs.appMode = PKG_MANAGER_MODE;
    app.paths.appConfigFile = paths.appConfigFile;
    if (!app.loadAppFile()) return app.errHandler.printErrors();
    for (const auto& package : app.appFile->packages) {
        const auto packageDir = paths.lgsPackagesDir / package.name;
        const auto versionStr = package.version.asStr();
        const auto fullName = package.name + ':' + versionStr;
        auto versionDir = packageDir / versionStr;
        const auto zipOutputFile = versionDir / (versionStr + ".zip");
        const auto srcOutputDir = versionDir / LGS_CODE_DIR;
        const auto downloadURL = package.path + "/archive/refs/tags/" + versionStr + ".zip";
        const auto unzippedDir = versionDir / (package.name + '-' + versionStr);
        const auto srcPath = versionDir / LGS_CODE_DIR;

        logDebug("Installing: " + fullName, true);
        createDir(versionDir);
        downloadFile(downloadURL, zipOutputFile);
        unzipFile(zipOutputFile, versionDir.string());
        assert(fs::exists(unzippedDir));
        if (fs::exists(srcPath)) {
            if (!fs::remove_all(unzippedDir)) assert(0);
        } else {
            std::error_code ec;
            fs::rename(unzippedDir, srcPath);
            if (ec) assert(0);
        }

        if (!fs::remove(zipOutputFile)) assert(0);
        logDebug(fullName + " installed successfully.", true);
    }
}

std::string calculateSHA256(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) assert(0);
    // Initialize OpenSSL hash context
    auto context = EVP_MD_CTX_new();
    if (!context) assert(0);
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        assert(0);
    }

    // Read file in chunks and update hash
    constexpr size_t bufferSize = 8192; // 8KB chunks
    char buffer[bufferSize];
    while (file.read(buffer, bufferSize) || file.gcount() > 0) {
        size_t bytesRead = file.gcount();
        if (EVP_DigestUpdate(context, buffer, bytesRead) != 1) {
            EVP_MD_CTX_free(context);
            assert(0);
        }
    }

    // Finalize hash
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen = 0;
    if (EVP_DigestFinal_ex(context, hash, &hashLen) != 1) {
        EVP_MD_CTX_free(context);
        assert(0);
    }
    EVP_MD_CTX_free(context);

    // Convert to hexadecimal string
    std::stringstream str;
    for (unsigned int i = 0; i < hashLen; i++) {
        str << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return str.str();
}
