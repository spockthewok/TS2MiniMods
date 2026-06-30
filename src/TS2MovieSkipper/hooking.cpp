#include "hooking.h"

namespace Hooking
{
    void Nop(BYTE *pAddress, DWORD dwLen)
    {
        DWORD dwOldProtect, dwBkup;

        VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);

        for (DWORD x = 0x0; x < dwLen; x++)
            *(pAddress + x) = 0x90;

        VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

        return;
    }
}