#include "Patches/unrestrictedchemistryui.h"
#include "hooking.h"
#include "TS2/base.h"

namespace
{
    const BYTE jmpByte = 0xEB;
    constexpr size_t byteSize = sizeof(BYTE);
}

namespace MiniMods
{
    void RemoveChemistryUIRestrictions()
    {
        // cTSNeighbor::GetChemistryBetween
        // Patches several chemistry validity checks to always be true
        Hooking::WriteToMemory((0x42EC16 + Module::base), &jmpByte, byteSize);
        Hooking::WriteToMemory((0x42EC44 + Module::base), &jmpByte, byteSize);
        Hooking::Nop((0x42ECDE + Module::base), 12);
        Hooking::WriteToMemory((0x42ECF2 + Module::base), &jmpByte, byteSize);
        Hooking::WriteToMemory((0x42ED0B + Module::base), &jmpByte, byteSize);
    }
}