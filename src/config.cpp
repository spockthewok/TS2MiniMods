#include "config.h"
#include "headers.h"
#include "include/ini.h"

namespace
{
    mINI::INIStructure ini;
    const std::filesystem::path configNameBase = "TS2MiniMods.ini";
    const std::filesystem::path configNameRPC = "mods/TS2MiniMods.ini";
}

namespace Config
{
    float slopeThreshold = 0.25;
    bool cineDrawDistance = true;
    bool elderCouplePoses = true;
    bool movieSkipper = false;
    bool noWebServices = true;
    bool unrestrictedChemistryUI = false;

    template <typename T>
    static T GetIniValue(const std::string &section, const std::string &key, T defaultValue)
    {
        if (!ini.has(section) || !ini[section].has(key))
            return defaultValue;

        const auto &value = ini[section][key];

        if constexpr (std::is_same_v<T, bool>)
            return (value == "true" || value == "1");
        else if constexpr (std::is_same_v<T, int>)
            return std::stoi(value);
        else if constexpr (std::is_same_v<T, float>)
            return std::stof(value);
        else if constexpr (std::is_same_v<T, double>)
            return std::stod(value);
        else if constexpr (std::is_same_v<T, std::string>)
            return value;

        return defaultValue;
    }

    static std::string GetModuleName()
    {
        char buffer[MAX_PATH];

        DWORD pathLen = GetModuleFileNameA(nullptr, buffer, MAX_PATH);

        if (pathLen == 0 || pathLen == MAX_PATH)
            return "";

        std::filesystem::path exePath(buffer);
        return exePath.filename().string();
    }

    void Init()
    {
        std::filesystem::path configName = configNameBase;

        if (GetModuleName().find("RPC.exe") != std::string::npos)
            configName = configNameRPC;

        mINI::INIFile file(configName);

        if (!file.read(ini))
            return;

        slopeThreshold = GetIniValue("AccurateImposterTerrain", "slopeThreshold", slopeThreshold);
        cineDrawDistance = GetIniValue("CineDrawDistance", "enabled", cineDrawDistance);
        elderCouplePoses = GetIniValue("ElderCouplePoses", "enabled", elderCouplePoses);
        movieSkipper = GetIniValue("MovieSkipper", "enabled", movieSkipper);
        noWebServices = GetIniValue("NoWebServices", "enabled", noWebServices);
        unrestrictedChemistryUI = GetIniValue("UnrestrictedChemistryUI", "enabled", unrestrictedChemistryUI);
    }
}