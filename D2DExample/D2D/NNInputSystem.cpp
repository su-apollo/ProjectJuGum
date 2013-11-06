
#include "NNInputSystem.h"
#include <windows.h>

NNInputSystem* NNInputSystem::m_pInstance = nullptr;

NNInputSystem::NNInputSystem()
{
	ZeroMemory( m_PrevKeyState, sizeof(m_PrevKeyState) );
	ZeroMemory( m_NowKeyState, sizeof(m_NowKeyState) );

	m_keyup = VK_UP;
	m_keydown = VK_DOWN;
	m_keyright = VK_RIGHT;
	m_keyleft = VK_LEFT;

}
NNInputSystem::~NNInputSystem()
{
}

NNInputSystem* NNInputSystem::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new NNInputSystem();
	}

	return m_pInstance;
}
void NNInputSystem::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void NNInputSystem::UpdateKeyState()
{
	for (int i=0; i<256; i++ )
	{
		m_PrevKeyState[i] = m_NowKeyState[i];

		if( ::GetKeyState(i) & 0x8000 )
		{
			m_NowKeyState[i] = true;
		}
		else
		{
			m_NowKeyState[i] = false;
		}
	}
}
KeyState NNInputSystem::GetKeyState( int key )
{
	if ( m_PrevKeyState[key] == false && m_NowKeyState[key] == true )
	{
		return KEY_DOWN;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == true )
	{
		return KEY_PRESSED;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == false )
	{
		return KEY_UP;
	}
	
	return KEY_NOTPRESSED;
}

InputSetUp NNInputSystem::GetDirectionKeyInput(void)
{
	if  (GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED)
	{
		return LEFT_UP;
	}
	else if (GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT_UP;
	}
	else if (GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		return LEFT_DOWN;
	}
	else if (GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && NNInputSystem::GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT_DOWN;
	}
	else if (GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		return LEFT;
	}
	else if (GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT;
	}
	else if (GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED )
	{
		return DOWN;
	}
	else if (GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED )
	{
		return UP;
	}
	else
		return ELSE;
}

InputSetUp NNInputSystem::GetSkillKeyInput(void)
{
	if (GetInstance()->GetKeyState('Z') == KEY_DOWN)
	{
		return SKILL_KEY_ONE;
	}
	else if (GetInstance()->GetKeyState('X') == KEY_DOWN)
	{
		return SKILL_KEY_TWO;
	}
	else if (GetInstance()->GetKeyState('C') == KEY_DOWN)
	{
		return SKILL_KEY_THREE;
	}
	else if (GetInstance()->GetKeyState('A') == KEY_DOWN)
	{
		return SKILL_KEY_FOUR;
	}
	else if (GetInstance()->GetKeyState('S') == KEY_DOWN)
	{
		return SKILL_KEY_FIVE;
	}
	else if (GetInstance()->GetKeyState('D') == KEY_DOWN)
	{
		return SKILL_KEY_SIX;
	}
	else if (GetInstance()->GetKeyState(VK_SPACE) == KEY_DOWN)
	{
		return UPGRADE_KEY;
	}
	else
		return ELSE;
}
