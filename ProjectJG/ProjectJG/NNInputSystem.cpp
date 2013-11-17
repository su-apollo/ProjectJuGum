#include "NNConfig.h"
#include "NNInputSystem.h"

NNInputSystem* NNInputSystem::m_pInstance = nullptr;

NNInputSystem::NNInputSystem()
{
	ZeroMemory( m_PrevKeyState, sizeof(m_PrevKeyState) );
	ZeroMemory( m_NowKeyState, sizeof(m_NowKeyState) );

	m_keyup = VK_UP;
	m_keydown = VK_DOWN;
	m_keyright = VK_RIGHT;
	m_keyleft = VK_LEFT;

	m_skill[0] = 'Z';
	m_skill[1] = 'X';
	m_skill[2] = 'C';
	m_skill[3] = 'A';
	m_skill[4] = 'S';
	m_skill[5] = 'D';

	m_upgradekey = VK_SPACE;
	m_changespeedkey = VK_SHIFT;
	m_pausekey = VK_ESCAPE;
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

EInputSetUp NNInputSystem::GetDirectionKeyInput(void)
{
	if  (GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED)
	{
		return LEFT_UP;
	}
	else if (GetInstance()->GetKeyState( m_keyup ) == KEY_PRESSED && GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
	{
		return RIGHT_UP;
	}
	else if (GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && GetInstance()->GetKeyState( m_keyleft ) == KEY_PRESSED )
	{
		return LEFT_DOWN;
	}
	else if (GetInstance()->GetKeyState( m_keydown ) == KEY_PRESSED && GetInstance()->GetKeyState( m_keyright ) == KEY_PRESSED )
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
		return NONE;
}

EInputSetUp NNInputSystem::GetSkillKeyInput(void)
{
	if (GetInstance()->GetKeyState(m_skill[0]) == KEY_DOWN)
	{
		return SKILL_KEY_ONE;
	}
	else if (GetInstance()->GetKeyState(m_skill[1]) == KEY_DOWN)
	{
		return SKILL_KEY_TWO;
	}
	else if (GetInstance()->GetKeyState(m_skill[2]) == KEY_DOWN)
	{
		return SKILL_KEY_THREE;
	}
	else if (GetInstance()->GetKeyState(m_skill[3]) == KEY_DOWN)
	{
		return SKILL_KEY_FOUR;
	}
	else if (GetInstance()->GetKeyState(m_skill[4]) == KEY_DOWN)
	{
		return SKILL_KEY_FIVE;
	}
	else if (GetInstance()->GetKeyState(m_skill[5]) == KEY_DOWN)
	{
		return SKILL_KEY_SIX;
	}
	else if (GetInstance()->GetKeyState(m_upgradekey) == KEY_DOWN)
	{
		return UPGRADE_KEY;
	}
	else
		return NONE;
}

EInputSetUp NNInputSystem::GetChangeSpeedKeyInput(void)
{
	if (GetInstance()->GetKeyState(m_changespeedkey) == KEY_PRESSED)
	{
		return CHANGE_SPEED;
	}
	else
		return NONE;
};

EInputSetUp NNInputSystem::GetMenuKeyInput(void)
{
	if (GetInstance()->GetKeyState(m_pausekey) == KEY_DOWN)
	{
		return PAUSE;
	}
	else
		return NONE;
};