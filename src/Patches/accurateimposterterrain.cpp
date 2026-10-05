#include "Patches/accurateimposterterrain.h"
#include "headers.h"
#include "config.h"

namespace
{
    const DWORD CreateDelauneyTerrainGeometry_Exit = 0xA003E0;
}

namespace MiniMods
{
    // cLotImposterManager::CreateDelauneyTerrainGeometry
    // Changes slope threshold required to add terrain vertex to imposter mesh
    // Vanilla value = 4.1
    void __declspec(naked) AlterImposterAccuracy()
    {
        __asm {
            fcomp [Config::slopeThreshold]
            jmp CreateDelauneyTerrainGeometry_Exit
        }
    }
}