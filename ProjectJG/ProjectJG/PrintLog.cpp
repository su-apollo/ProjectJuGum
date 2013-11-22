#include "NNConfig.h"
#include "PrintLog.h"

PrintLog* PrintLog::m_pInstance = nullptr;

PrintLog* PrintLog::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new PrintLog();
	}

	return m_pInstance;
}

void PrintLog::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

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
