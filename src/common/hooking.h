#pragma once
#include "headers.h"

namespace Hooking
{
	void Nop(BYTE *pAddress, DWORD dwLen);
	void WriteToMemory(DWORD addressToWrite, char *valueToWrite, int byteNum);
	void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen);
}