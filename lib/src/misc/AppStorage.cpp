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
    const auto appdataPath =
        std::filesystem::path(sf::getNativeActivity()->internalDataPath);
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
    return dgm::Utility::loadFileAllText(appdataPath / file);
}

void InternalStorage::saveFile(
    const std::filesystem::path& file, const std::string& data)
{
    const auto appdataPath = getAppdataPath();
    std::ofstream save(appdataPath / file);
    save.write(data.c_str(), data.size());
}
