#include "Patches/nowebservices.h"
#include "hooking.h"
#include "TS2/base.h"

namespace
{
    const BYTE contentBrowserJmp[] = {0xE9, 0x8B, 0x00, 0x00, 0x00};
    const BYTE lotMetadataJmp[] = {0xE9, 0x6C, 0x01, 0x00, 0x00};
    const BYTE jmpByte = 0xEB;
    constexpr size_t jmpSize = sizeof(contentBrowserJmp);
}

namespace MiniMods
{
    void DisableWebServices()
    {
        // TSAppHookAddGeneralCOMDirectors & TSAppHookStartGeneralCOMDirectors
        Hooking::Nop((0x1122 + Module::base), 11);
        Hooking::Nop((0x11B8 + Module::base), 13);
        // cTSUIDialogManager::ShowContentBrowserDialog
        // Forces the content browser dialogue method to immediately return
        Hooking::WriteToMemory((0xA4970 + Module::base), contentBrowserJmp, jmpSize);
        // cTSCustomContentSupport::CollectFilesForLot
        // Game tries to add Exchange metadata to file when packaging a lot
        // Relies on the web services we disabled, so always fails
        // This bypasses the failure check to allow the lot to still be packaged
        Hooking::WriteToMemory((0x5E0251 + Module::base), lotMetadataJmp, jmpSize);
        // cTSCustomContentSupport::CollectFilesForOutfit
        Hooking::WriteToMemory((0x5DE785 + Module::base), &jmpByte, sizeof(BYTE));
    }
}