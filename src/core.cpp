#include "core.h"
#include "hooking.h"
#include "config.h"
#include "TS2/base.h"
#include "Patches/accurateimposterterrain.h"
#include "Patches/cinedrawdistance.h"
#include "Patches/eldercoupleposes.h"
#include "Patches/hiddencheats.h"
#include "Patches/movieskipper.h"
#include "Patches/nowebservices.h"
#include "Patches/unrestrictedchemistryui.h"

namespace Core
{
    static void InjectPatches()
    {
        Hooking::MakeJMP((0x6003DA + Module::base), (DWORD)(MiniMods::AlterImposterAccuracy), 6);

        if (Config::cineDrawDistance)
            Hooking::MakeJMP((0xB947A1 + Module::base), (DWORD)MiniMods::IncreaseCineDrawDistance, 6);

        if (Config::effectCheats)
            MiniMods::RestoreEffectCheats();

        if (Config::allowAllCheats)
            Hooking::MakeJMP((0x90DAA0 + Module::base), (DWORD)MiniMods::AllowTestingCheats, 7);

        if (Config::elderCouplePoses)
            MiniMods::AllowElderCouplePoses();

        if (Config::movieSkipper)
            MiniMods::DisableIntroMovies();

        if (Config::noWebServices)
            MiniMods::DisableWebServices();

        if (Config::unrestrictedChemistryUI)
            MiniMods::RemoveChemistryUIRestrictions();
    }

    void Init()
    {
        Module::base = reinterpret_cast<DWORD>(GetModuleHandleA(NULL));

        Config::Init();
        InjectPatches();
    }
}