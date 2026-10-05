#include "Patches/movieskipper.h"
#include "hooking.h"
#include "core.h"

namespace MiniMods
{
    void DisableIntroMovies()
    {
        // cTSWinProcGameLoad::onTick()
        Hooking::Nop(reinterpret_cast<BYTE *>(0x1AFF30 + Core::modBase), 5); // ealogo_audio.movie
        Hooking::Nop(reinterpret_cast<BYTE *>(0x1B0172 + Core::modBase), 5); // intro_eng_audio.movie
    }
}