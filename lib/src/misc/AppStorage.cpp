#include "misc/AppStorage.hpp"
#include "misc/CMakeVars.hpp"
#include <DGM/classes/Utility.hpp>
#include <filesystem>
#include <fstream>

#ifdef ANDROID
#include <jni/Jni.hpp>
#else
#include <Windows.h>
#include <codecvt>
#include <shlobj.h>
#include <shlobj_core.h>
#endif

std::filesystem::path getAppdataPath()
{
#ifdef ANDROID
    return std::filesystem::path(sf::getNativeActivity()->externalDataPath);
#else
    PWSTR raw;
    std::wstring result;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &raw) == S_OK)
    {
        result = std::wstring(raw);
    }
    CoTaskMemFree(raw);

    // Need to convert wstring to string
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    return CMakeVars::TITLE / std::filesystem::path(converter.to_bytes(result));
#endif
}

std::expected<std::string, dgm::Error>
InternalStorage::loadFile(const std::filesystem::path& file)
{
    const auto appdataPath = getAppdataPath();
    std::ifstream load(appdataPath / file);
    load.seekg(0, std::ios::end);
    size_t fileLen = load.tellg();
    load.seekg(0, std::ios::beg);

    auto&& result = std::string(fileLen, '\0');
    load.read(result.data(), fileLen);

    return result;
}

void InternalStorage::saveFile(
    const std::filesystem::path& file, const std::string& data)
{
    const auto appdataPath = getAppdataPath();
    std::ofstream save(appdataPath / file);
    save.write(data.c_str(), data.size());
}
