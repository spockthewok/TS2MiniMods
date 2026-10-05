#include "Patches/nowebservices.h"
#include "hooking.h"
#include "core.h"

namespace
{
    const BYTE contentBrowserJmp[] = {0xE9, 0x8B, 0x00, 0x00, 0x00};
    constexpr size_t jmpSize = sizeof(contentBrowserJmp);
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
    }
}