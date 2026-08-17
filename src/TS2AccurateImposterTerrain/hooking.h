#pragma once
#include "headers.h"

namespace Hooking
{
	void WriteToMemory(DWORD addressToWrite, char *valueToWrite, int byteNum);
}