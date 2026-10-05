#include "Patches/eldercoupleposes.h"
#include "hooking.h"
#include "core.h"

namespace
{
    const BYTE maxAge = 0x33;
    constexpr size_t byteSize = sizeof(maxAge);
}

namespace MiniMods
{
    // cTSUIThumbnailFactoryFamily::FindCouples
    // if (32 < sVar2) -> if (33 < sVar2)
    void AllowElderCouplePoses()
    {
        Hooking::WriteToMemory((0x3AA7E + Core::modBase), &maxAge, byteSize);
    }
}