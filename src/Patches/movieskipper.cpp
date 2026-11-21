#include "Patches/movieskipper.h"
#include "hooking.h"
#include "TS2/base.h"

namespace MiniMods
{
    void DisableIntroMovies()
    {
        // cTSWinProcGameLoad::onTick
        Hooking::Nop((0x1AFF30 + Module::base), 5); // ealogo_audio.movie
        Hooking::Nop((0x1B0172 + Module::base), 5); // intro_eng_audio.movie
    }
}