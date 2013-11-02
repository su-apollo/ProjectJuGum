#include "InputManager.h"
#include "NNInputSystem.h"

CInputManager* CInputManager::pInstance = NULL;

CInputManager::CInputManager(void)
{
	m_keyup = VK_UP;
	m_keydown = VK_DOWN;
	m_keyright = VK_RIGHT;
	m_keyleft = VK_LEFT;
}


CInputManager::~CInputManager(void)
{
}


Directions CInputManager::GetDirectionKeyInput(void)
{
	if  (NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED)
	{
		return LEFT_UP;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT_UP;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		return LEFT_DOWN;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT_DOWN;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		return LEFT;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED )
	{
		return DOWN;
	}
	else if ( NNInputSystem::GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED )
	{
		return UP;
	}
	else
		return WRONG_INPUT;
}


CInputManager* CInputManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new CInputManager();
	}
	return pInstance;
}
