#pragma once

class PrintLog
{
public:
	static PrintLog* GetInstance();
	static void ReleaseInstance();

private:
	static PrintLog* m_pInstance;

	PrintLog(void);
	~PrintLog(void);
};

