#include "core.h"
#include "hooking.h"
#include "config.h"
#include "Patches/accurateimposterterrain.h"
#include "Patches/cinedrawdistance.h"
#include "Patches/eldercoupleposes.h"
#include "Patches/movieskipper.h"
#include "Patches/nowebservices.h"
#include "Patches/unrestrictedchemistryui.h"

namespace Core
{
    DWORD modBase;

    static void InjectPatches()
    {
        modBase = reinterpret_cast<DWORD>(GetModuleHandleA(NULL));

        Hooking::MakeJMP((BYTE *)(0x6003DA + modBase), (DWORD)(MiniMods::AlterImposterAccuracy), 6);

        if (Config::cineDrawDistance)
            MiniMods::IncreaseCineDrawDistance();

        if (Config::elderCouplePoses)
            MiniMods::AllowElderCouplePoses();

        if (Config::movieSkipper)
            MiniMods::DisableIntroMovies();

        if (Config::noWebServices)
            MiniMods::DisableWebServices();

        if (Config::unrestrictedChemistryUI)
            MiniMods::RemoveChemistryRestrictions();
    }

    void Init()
    {
        Config::Init();
        InjectPatches();
    }
}