#include "BulletManager.h"


CBulletManager* CBulletManager::m_pInstance = nullptr;

CBulletManager::CBulletManager(void)
{
}


CBulletManager::~CBulletManager(void)
{
}



CBulletManager* CBulletManager::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CBulletManager();
	}

	return m_pInstance;
}
void CBulletManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}