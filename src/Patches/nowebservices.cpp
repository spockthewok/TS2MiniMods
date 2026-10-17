#include "Patches/nowebservices.h"
#include "hooking.h"
#include "core.h"

namespace
{
    const BYTE contentBrowserJmp[] = {0xE9, 0x8B, 0x00, 0x00, 0x00};
    const BYTE lotMetadataJmp[] = {0xE9, 0x6C, 0x01, 0x00, 0x00};
    const BYTE jmpByte = 0xEB;
    constexpr size_t jmpSize = sizeof(contentBrowserJmp);
    constexpr size_t byteSize = sizeof(jmpByte);
}

namespace MiniMods
{
    void DisableWebServices()
    {
        // TSAppHookAddGeneralCOMDirectors & TSAppHookStartGeneralCOMDirectors
        Hooking::Nop(reinterpret_cast<BYTE *>(0x1122 + Core::modBase), 11);
        Hooking::Nop(reinterpret_cast<BYTE *>(0x11B8 + Core::modBase), 13);
        // cTSUIDialogManager::ShowContentBrowserDialog
        // Forces the content browser dialogue method to immediately return
        Hooking::WriteToMemory((0xA4970 + Core::modBase), contentBrowserJmp, jmpSize);
        // cTSCustomContentSupport::CollectFilesForLot
        // Game tries to add Exchange metadata to file when packaging a lot
        // Relies on the web services we disabled, so always fails
        // This bypasses the failure check to allow the lot to still be packaged
        Hooking::WriteToMemory((0x5E0251 + Core::modBase), lotMetadataJmp, jmpSize);
        // cTSCustomContentSupport::CollectFilesForOutfit
        Hooking::WriteToMemory((0x5DE785 + Core::modBase), &jmpByte, byteSize);
    }
}