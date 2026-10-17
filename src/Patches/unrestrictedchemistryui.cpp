#include "Patches/unrestrictedchemistryui.h"
#include "hooking.h"
#include "core.h"

namespace
{
    const BYTE jmpByte = 0xEB;
    constexpr size_t byteSize = sizeof(jmpByte);
}

namespace MiniMods
{
    void RemoveChemistryRestrictions()
    {
        // cTSNeighbor::GetChemistryBetween
        // Patches several chemistry validity checks to always be true
        Hooking::WriteToMemory((0x42EC16 + Core::modBase), &jmpByte, byteSize);
        Hooking::WriteToMemory((0x42EC44 + Core::modBase), &jmpByte, byteSize);
        Hooking::Nop(reinterpret_cast<BYTE *>(0x42ECDE + Core::modBase), 12);
        Hooking::WriteToMemory((0x42ECF2 + Core::modBase), &jmpByte, byteSize);
        Hooking::WriteToMemory((0x42ED0B + Core::modBase), &jmpByte, byteSize);
    }
}