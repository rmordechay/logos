#include "logos/LgsPkgManager.h"
#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"
#include "curl/curl.h"
#include "miniz.h"
#include "files/LgsAppConfigFile.h"
#include "logos/LgsApp.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <openssl/evp.h>

namespace fs = std::filesystem;
#define MAX_DOWNLOAD_FILE_SIZE 10'000 * 1024

bool unzipFile(const std::string& zipPath, const std::string& destDir) {
    mz_zip_archive archive = {};
    if (!mz_zip_reader_init_file(&archive, zipPath.c_str(), 0)) return false;
    const auto numFiles = mz_zip_reader_get_num_files(&archive);
    for (mz_uint i = 0; i < numFiles; ++i) {
        mz_zip_archive_file_stat file_stat;
        mz_zip_reader_file_stat(&archive, i, &file_stat);
        auto fullPath = fs::path(destDir) / file_stat.m_filename;
        auto dirPath = fullPath.parent_path();
        createDir(dirPath);
        if (mz_zip_reader_is_file_a_directory(&archive, i)) continue;
        mz_zip_reader_extract_to_file(&archive, i, fullPath.string().c_str(), 0);
    }
    mz_zip_reader_end(&archive);
    return true;
}

size_t write_data(void* ptr, const size_t size, const size_t nmemb, void* stream) {
    const auto out = static_cast<std::ofstream*>(stream);
    out->write(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

bool downloadFile(const std::string& url, const std::string& outPath) {
    assert(url.substr(0, 8) == "https://");
    const auto curl = curl_easy_init();
    if (!curl) return false;
    std::ofstream outFile(outPath, std::ios::binary);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXFILESIZE_LARGE, MAX_DOWNLOAD_FILE_SIZE);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);
    const auto res = curl_easy_perform(curl);
    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    if (res != CURLE_OK) logError(curl_easy_strerror(res));
    curl_easy_cleanup(curl);
    outFile.close();
    return res == CURLE_OK;
}

void LgsPkgManager::install() {
    paths.findLgsRootDir();
    assert(fs::exists(paths.lgsPackagesDir));
    LgsApp app;
    app.configs.appMode = PKG_MANAGER_MODE;
    app.paths.appConfigFile = paths.appConfigFile;
    if (!app.loadConfigFile()) return app.errHandler.printErrors();
    for (const auto& package : app.appConfigFile->packages) {
        const auto packageDir = paths.lgsPackagesDir / package.name;
        const auto versionStr = package.version.asStr();
        const auto fullName = package.name + ':' + versionStr;
        auto versionDir = packageDir / versionStr;
        const auto zipOutputFile = versionDir / (versionStr + ".zip");
        const auto srcOutputDir = versionDir / LGS_CODE_DIR;
        const auto downloadURL = package.url + "/archive/refs/tags/" + versionStr + ".zip";
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
