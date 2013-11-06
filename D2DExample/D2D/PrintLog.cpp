#include "PrintLog.h"
#include <consoleapi.h>
#include <stdio.h>


PrintLog::PrintLog(void)
{
	AllocConsole();
	FILE* pStream;
	freopen_s(&pStream, "CONOUT$", "wt", stdout);
}


PrintLog::~PrintLog(void)
{
	FreeConsole();
}