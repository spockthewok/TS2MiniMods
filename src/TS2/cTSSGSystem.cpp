#include "TS2/cTSSGSystem.h"
#include "common.h"

namespace nTSSG
{
    bool cTSSGSystem::IsCinematicSceneActive()
    {
        using Func = bool(__thiscall *)(cTSSGSystem *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0xE0);
        return vFunc(this);
    }
}